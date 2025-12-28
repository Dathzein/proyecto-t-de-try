#include "Player.h" // Incluye el encabezado de la clase Player

// Constructor de la clase Player
Player::Player() {
  shape.setSize({40, 40}); // Establece el tamaño del jugador a 40x40 píxeles
  shape.setFillColor(sf::Color::Red); // Color del jugador: Rojo
  shape.setPosition({100, 300});      // Posición inicial (x=100, y=300)
  velocityY = 0;                      // Inicializa la velocidad vertical en 0
  velocityX = 0;                      // Inicializa la velocidad horizontal en 0
  isJumping = false;                  // No está saltando inicialmente
  isCrouching = false;                // No está agachado inicialmente
  moveLeft = false;                   // No se está moviendo a la izquierda
  moveRight = false;                  // No se está moviendo a la derecha
}

// Método para procesar las entradas del teclado
void Player::handleInput(sf::Keyboard::Key key, bool isPressed) {
  if (key == sf::Keyboard::Key::A) { // Si la tecla es 'A'
    moveLeft = isPressed; // Activa o desactiva el movimiento a la izquierda
  } else if (key == sf::Keyboard::Key::D) { // Si la tecla es 'D'
    moveRight = isPressed; // Activa o desactiva el movimiento a la derecha
  } else if (key == sf::Keyboard::Key::Q) { // Si la tecla es 'Q' (Agacharse)
    if (isPressed) {                        // Si se presiona
      if (!isCrouching) {                   // Y no estaba agachado
        isCrouching = true;                 // Marca estado agachado
        shape.setSize({40, 20});            // Reduce la altura a la mitad
        shape.setOrigin({0, 0});            // Mantiene el origen
        // Ajusta posición Y hacia abajo para mantener contacto con el suelo
        if (!isJumping)
          shape.setPosition({shape.getPosition().x, 320});
      }
    } else {                     // Si se suelta 'Q'
      if (isCrouching) {         // Y estaba agachado
        isCrouching = false;     // Marca estado de pie
        shape.setSize({40, 40}); // Restaura el tamaño original
        // Restaura posición Y hacia arriba
        if (!isJumping)
          shape.setPosition({shape.getPosition().x, 300});
      }
    }
  } else if (key ==
             sf::Keyboard::Key::Space) { // Si la tecla es Espacio (Saltar)
    // Si se presiona, no está ya saltando y no está agachado
    if (isPressed && !isJumping && !isCrouching) {
      velocityY = -12;  // Aplica una fuerza negativa (hacia arriba)
      isJumping = true; // Marca estado saltando
    }
  }
}

// Método de actualización lógica por frame
void Player::update() {
  // Movimiento Horizontal
  velocityX = 0; // Reinicia velocidad horizontal
  if (moveLeft)
    velocityX = -5; // Si moveLeft es true, velocidad negativa
  if (moveRight)
    velocityX = 5; // Si moveRight es true, velocidad positiva

  shape.move({velocityX, 0}); // Mueve el objeto horizontalmente

  // Límites de pantalla (0 a 800 de ancho)
  if (shape.getPosition().x < 0)
    shape.setPosition({0, shape.getPosition().y}); // Límite izquierdo
  if (shape.getPosition().x > 760)
    shape.setPosition(
        {760, shape.getPosition().y}); // Límite derecho (800 - ancho 40)

  velocityY += 0.5f;          // Aplica gravedad (aumenta velocidad hacia abajo)
  shape.move({0, velocityY}); // Mueve el objeto verticalmente

  // Colisión con el suelo
  float groundY =
      isCrouching
          ? 320.0f
          : 300.0f; // Define la altura del suelo según si está agachado o no

  // Si la posición Y supera el suelo
  if (shape.getPosition().y >= groundY) {
    shape.setPosition(
        {shape.getPosition().x, groundY}); // Fija la posición en el suelo
    velocityY = 0;                         // Detiene la caída
    isJumping = false;                     // Permite volver a saltar
  }
}

sf::RectangleShape Player::getShape() {
  return shape;
} // Retorna el objeto gráfico

sf::FloatRect Player::getBounds() {
  return shape.getGlobalBounds();
} // Retorna el rectángulo de colisión