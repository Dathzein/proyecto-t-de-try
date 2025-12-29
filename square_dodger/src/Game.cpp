#include "Game.h"   // Incluye el encabezado de la clase Game
#include <cstdlib>  // Incluye biblioteca para rand() y srand()
#include <ctime>    // Incluye biblioteca para time()
#include <iostream> // Incluye la biblioteca para entrada/salida estándar

// Constructor de la clase Game
Game::Game()
    : window(sf::VideoMode(sf::Vector2u(800, 400)),
             "Square Dodger"), // Inicializa la ventana con resolución 800x400 y
                               // título
      uiText(font),     // Inicializa texto de UI con la fuente
      scoreText(font) { // Inicializa texto de puntuación con la fuente

  std::srand(static_cast<unsigned>(std::time(
      nullptr))); // Semilla para números aleatorios basada en el tiempo actual
  window.setFramerateLimit(
      60); // Limita la ejecución a 60 cuadros por segundo (FPS)

  // Carga de la fuente para textos
  if (!font.openFromFile("assets/Arial.ttf")) {
    // Muestra error en consola si falla la carga
    std::cerr << "Failed to load font" << std::endl;
  }

  // Configuración del texto de UI (Mensajes de fin de juego)
  uiText.setFont(font);
  uiText.setCharacterSize(24);
  uiText.setFillColor(sf::Color::Black);

  // Configuración del texto de Puntuación
  scoreText.setFont(font);
  scoreText.setCharacterSize(20);
  scoreText.setFillColor(sf::Color::Black);
  scoreText.setPosition(
      {10.f, 10.f}); // Posición en la esquina superior izquierda

  resetGame(); // Llama a la función para iniciar/reiniciar variables del juego
}

// Restablece todas las variables del juego a su estado inicial
void Game::resetGame() {
  score = 0;          // Reinicia puntuación
  gameWon = false;    // Reinicia estado de victoria
  isGameOver = false; // Reinicia estado de Game Over
  spawnTimer = 0;     // Reinicia temporizador de generación de obstáculos
  obstacles.clear();  // Elimina todos los obstáculos de la lista

  // Crea un nuevo objeto Player, reiniciando su posición y estado
  player = Player();
}

// Bucle principal de ejecución del juego
void Game::run() {
  while (window.isOpen()) { // Se mantiene ejecutando mientras la ventana esté
                            // abierta
    processEvents();        // 1. Procesa entradas del usuario (teclado/mouse)
    update(); // 2. Actualiza la lógica del juego (movimiento, colisiones)
    render(); // 3. Dibuja todo en la pantalla
  }
}

// Maneja los eventos del sistema y del usuario
void Game::processEvents() {
  while (const auto event =
             window.pollEvent()) { // Itera sobre la cola de eventos
    // Si el evento es cerrar la ventana (clic en X)
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    // Detección de teclas presionadas
    if (const auto *keyEvent = event->getIf<sf::Event::KeyPressed>()) {
      player.handleInput(keyEvent->code,
                         true); // Notifica al jugador que se presionó una tecla

      // Tecla 'R' para reiniciar el juego
      if (keyEvent->code == sf::Keyboard::Key::R) {
        resetGame();
      }
    }

    // Detección de teclas liberadas (soltadas)
    if (const auto *keyEvent = event->getIf<sf::Event::KeyReleased>()) {
      player.handleInput(keyEvent->code,
                         false); // Notifica al jugador que se soltó una tecla
    }
  }
}

// Actualiza el estado del mundo del juego (lógica por frame)
void Game::update() {
  if (isGameOver) // Si el juego terminó, no actualizamos nada más
    return;

  player.update(); // Actualiza físicas y movimiento del jugador

  // --- Lógica de Generación de Obstáculos ---
  if (spawnTimer <
      60) { // Cuenta frames. Si es menor a 60 (aprox 1 segundo a 60FPS)
    spawnTimer++;
  } else {
    // Intenta generar si no hay obstáculos O el último ya avanzó lo suficiente
    // (x < 600) Esto asegura un espacio mínimo entre obstáculos
    if (obstacles.empty() ||
        obstacles.back().getShape().getPosition().x < 600) {

      // Decisión aleatoria del tipo de obstáculo
      int r = rand() % 2; // Genera 0 o 1
      // Si es 0 -> GROUND (Suelo), Si es 1 -> AIR (Aéreo)
      ObstacleType type = (r == 0) ? ObstacleType::GROUND : ObstacleType::AIR;

      obstacles.emplace_back(type); // Crea y añade el obstáculo a la lista
      spawnTimer = 0; // Reinicia el contador para el próximo spawn
    }
  }

  // --- Actualización de Obstáculos y Colisiones ---
  // Iteramos sobre la lista de obstáculos
  for (auto it = obstacles.begin(); it != obstacles.end();) {
    it->update(); // Mueve el obstáculo actual

    // Chequeo de colisión: Intersección entre rectángulos del jugador y
    // obstáculo
    if (it->getBounds().findIntersection(player.getBounds())) {
      isGameOver = true; // Activa Game Over
      gameWon = false;
      uiText.setString("GAME OVER - Press R to Restart"); // Prepara mensaje

      // Centra el texto en la pantalla
      sf::FloatRect textRect = uiText.getLocalBounds();
      uiText.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                        textRect.position.y + textRect.size.y / 2.0f});
      uiText.setPosition({400.f, 200.f});
    }

    // Chequeo de obstáculo fuera de pantalla (izquierdo) y Puntuación
    // Si la posición X + ancho es menor a 0, salió completamente
    if (it->getShape().getPosition().x + it->getShape().getSize().x < 0) {
      score++; // Incrementa puntuación por esquivar
      it = obstacles.erase(
          it); // Elimina el obstáculo de la memoria y actualiza iterador
    } else {
      ++it; // Avanza al siguiente obstáculo si no fue borrado
    }
  }

  // --- Condición de Victoria ---
  if (score >= 100) {
    isGameOver = true;                                 // Detiene el juego
    gameWon = true;                                    // Marca victoria
    uiText.setString("YOU WIN! - Press R to Restart"); // Mensaje de victoria
    sf::FloatRect textRect = uiText.getLocalBounds();
    uiText.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                      textRect.position.y + textRect.size.y / 2.0f});
    uiText.setPosition({400.f, 200.f});
  }

  // Actualiza el texto de la puntuación en pantalla
  scoreText.setString("Score: " + std::to_string(score));
}

// Renderiza todos los elementos gráficos en la ventana
void Game::render() {
  window.clear(
      sf::Color::White); // 1. Limpia el frame anterior con color blanco

  window.draw(player.getSprite()); // 2. Dibuja al jugador

  // 3. Dibuja todos los obstáculos activos
  for (auto &obs : obstacles) {
    window.draw(obs.getShape());
  }

  window.draw(scoreText); // 4. Dibuja interfáz de puntuación

  // 5. Si el juego terminó, dibuja el mensaje de Game Over / Win
  if (isGameOver) {
    window.draw(uiText);
  }

  window.display(); // 6. Muestra lo dibujado en la pantalla física
}