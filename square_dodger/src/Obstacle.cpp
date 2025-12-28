#include "Obstacle.h" // Incluye la definición de la clase Obstacle

// Constructor: Configura el obstáculo según su tipo (Suelo o Aire)
Obstacle::Obstacle(ObstacleType type) {
  shape.setSize({40, 40}); // Establece el tamaño del obstáculo a 40x40 píxeles

  // Configuración específica según el tipo de obstáculo
  if (type == ObstacleType::AIR) {
    shape.setFillColor(sf::Color::Yellow); // Color amarillo para diferenciarlo
    shape.setPosition({800, 275});         // Posición elevada (Y=275)
    // Nota: El jugador de pie llega a Y=300 (colisiona).
    // El jugador agachado baja su altura, evitando el área 275-315.
  } else {
    // Por defecto (GROUND), color azul y posición a ras de suelo
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition({800, 290}); // Posición baja (Y=290), requiere salto
  }
}

// Actualiza la posición del obstáculo
void Obstacle::update() {
  shape.move(
      {-5, 0}); // Mueve el obstáculo 5 píxeles a la izquierda en cada frame

  // Lógica de reciclaje (Nota: Actualmente el juego elimina obstáculos fuera de
  // pantalla, por lo que este bloque rara vez actuaría si se destruyen antes de
  // llegar a -50)
  if (shape.getPosition().x < -50) {
    shape.setPosition({800, 290});
  }
}

// Devuelve el objeto gráfico para ser renderizado en la ventana
sf::RectangleShape Obstacle::getShape() { return shape; }

// Devuelve los límites globales para comprobar colisiones con el jugador
sf::FloatRect Obstacle::getBounds() { return shape.getGlobalBounds(); }