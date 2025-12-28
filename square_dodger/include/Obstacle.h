#pragma once // Directiva para incluir este archivo solo una vez en la
             // compilación
#include <SFML/Graphics.hpp> // Incluye la librería gráfica de SFML

// Enumeración para definir los tipos de obstáculos disponibles
enum class ObstacleType {
  GROUND, // Obstáculo de suelo (se debe saltar)
  AIR     // Obstáculo aéreo (se debe agachar con 'Q')
};

class Obstacle {
public:
  // Constructor: Recibe el tipo de obstáculo para configurarlo
  Obstacle(ObstacleType type);

  // Método para actualizar la posición del obstáculo en cada frame
  void update();

  // Retorna la forma gráfica del obstáculo para dibujarlo
  sf::RectangleShape getShape();

  // Retorna el rectángulo de límites para detectar colisiones
  sf::FloatRect getBounds();

private:
  sf::RectangleShape shape; // La forma geométrica (rectángulo) del obstáculo
};