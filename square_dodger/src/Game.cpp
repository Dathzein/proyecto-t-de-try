#include "Game.h" // Incluye el encabezado de Game
#include <iostream> // Incluye la biblioteca E/S estándar (aunque no se use mucho aquí ya)

// Constructor de Game
Game::Game()
    : window(sf::VideoMode(sf::Vector2u(800, 400)),
             "Square Dodger"), // Crea la ventana de 800x400
      uiText(font),
      scoreText(font) {         // Inicializa los textos de la UI con la fuente
  window.setFramerateLimit(60); // Limita el juego a 60 cuadros por segundo

  if (!font.openFromFile("assets/Arial.ttf")) { // Intenta cargar la fuente
    // Manejo de errores si falla la carga
    std::cerr << "Failed to load font" << std::endl;
  }
  uiText.setFont(font);                  // Asigna la fuente al texto de UI
  uiText.setCharacterSize(24);           // Tamaño de letra
  uiText.setFillColor(sf::Color::Black); // Color negro

  scoreText.setFont(font);        // Asigna fuente al texto de puntuación
  scoreText.setCharacterSize(20); // Tamaño de letra
  scoreText.setFillColor(sf::Color::Black); // Color negro
  scoreText.setPosition({10.f, 10.f});      // Posición arriba a la izquierda

  resetGame(); // Inicializa las variables del juego
}

// Reinicia el juego a su estado original
void Game::resetGame() {
  score = 0;          // Puntuación a 0
  gameWon = false;    // Reinicia bandera de ganar
  isGameOver = false; // Reinicia bandera de Game Over
  spawnTimer = 0;     // Reinicia temporizador de obstáculos
  obstacles.clear();  // Elimina todos los obstáculos existentes

  // Reinicia la posición del jugador creando uno nuevo
  player = Player();
}

// Bucle principal del juego
void Game::run() {
  while (window.isOpen()) { // Mientras la ventana esté abierta
    processEvents();        // Procesa entradas
    update();               // Actualiza lógica
    render();               // Dibuja en pantalla
  }
}

// Procesa eventos de la ventana y teclado
void Game::processEvents() {
  while (const auto event = window.pollEvent()) { // Obtiene eventos de la cola
    if (event->is<sf::Event::Closed>()) {         // Si se cierra la ventana
      window.close();                             // Cierra la ventana
    }

    // Si se presiona una tecla
    if (const auto *keyEvent = event->getIf<sf::Event::KeyPressed>()) {
      player.handleInput(keyEvent->code, true); // Pasa la entrada al jugador

      if (keyEvent->code == sf::Keyboard::Key::R) { // Si es 'R', reinicia
        resetGame(); // Llama a la función para reiniciar el juego
      }
    }

    // Si se suelta una tecla
    if (const auto *keyEvent = event->getIf<sf::Event::KeyReleased>()) {
      player.handleInput(keyEvent->code,
                         false); // Informa al jugador que la tecla fue soltada
    }
  }
}

// Actualiza la lógica del juego
void Game::update() {
  if (isGameOver) // Si el juego terminó, no hace nada
    return;

  player.update(); // Actualiza al jugador

  // Generación de obstáculos
  if (spawnTimer < 60) { // Si el temporizador es menor a 60 frames (1 seg)
    spawnTimer++;        // Incrementa
  } else {
    // Si no hay obstáculos o el último está lejos (x < 600)
    if (obstacles.empty() ||
        obstacles.back().getShape().getPosition().x < 600) {
      obstacles.emplace_back(); // Agrega nuevo obstáculo
      spawnTimer = 0;           // Reinicia timer
    }
  }

  // Actualiza obstáculos y revisa colisiones
  for (auto it = obstacles.begin(); it != obstacles.end();) {
    it->update(); // Mueve el obstáculo

    // Colisión con el jugador
    if (it->getBounds().findIntersection(player.getBounds())) {
      isGameOver = true;                                  // Fin del juego
      gameWon = false;                                    // No ganó
      uiText.setString("GAME OVER - Press R to Restart"); // Mensaje

      // Centra el texto en pantalla
      sf::FloatRect textRect = uiText.getLocalBounds();
      uiText.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                        textRect.position.y + textRect.size.y / 2.0f});
      uiText.setPosition({400.f, 200.f});
    }

    // Puntuación y limpieza de obstáculos
    // Si el obstáculo salió de la pantalla por la izquierda
    if (it->getShape().getPosition().x + it->getShape().getSize().x < 0) {
      score++;                  // Aumenta puntaje
      it = obstacles.erase(it); // Elimina el obstáculo de la memoria
    } else {
      ++it; // Siguiente obstáculo
    }
  }

  // Condición de Victoria
  if (score >= 100) {
    isGameOver = true;                                 // Detiene el juego
    gameWon = true;                                    // Marca victoria
    uiText.setString("YOU WIN! - Press R to Restart"); // Mensaje
    sf::FloatRect textRect = uiText.getLocalBounds();
    uiText.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                      textRect.position.y + textRect.size.y / 2.0f});
    uiText.setPosition({400.f, 200.f});
  }

  scoreText.setString("Score: " +
                      std::to_string(score)); // Actualiza texto de score
}

// Renderiza (dibuja) la escena
void Game::render() {
  window.clear(sf::Color::White); // Limpia pantalla con blanco

  window.draw(player.getShape()); // Dibuja al jugador

  // Dibuja todos los obstáculos
  for (auto &obs : obstacles) {
    window.draw(obs.getShape());
  }

  window.draw(scoreText); // Dibuja la puntuación

  // Si el juego terminó, dibuja el mensaje final
  if (isGameOver) {
    window.draw(uiText);
  }

  window.display(); // Muestra el frame en pantalla
}