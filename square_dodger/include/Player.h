#pragma once // Directiva para asegurar que el archivo se incluya solo una vez
#include <SFML/Graphics.hpp> // Incluye la biblioteca gráfica de SFML
#include <vector>

class Player { // Definición de la clase Player (Jugador)
public:
  Player(); // Constructor: inicializa al jugador
  void handleInput(sf::Keyboard::Key key,
                   bool isPressed); // Método para manejar entradas de teclado
                                    // (presionar/soltar)
  struct SupportSurface {
    sf::FloatRect bounds; // Rect del tile/plataforma (top-left + size)
    float velocityX;      // Velocidad X de la plataforma (para "carry")
  };

  // Actualiza la lógica del jugador (permite aterrizar sobre plataformas)
  void update(const std::vector<SupportSurface> &surfaces);
  const sf::Sprite &getSprite() const; // Retorna el sprite del jugador
  sf::FloatRect getBounds();     // Retorna los límites de colisión del jugador

private:
  // Render
  sf::Texture idleTexture;
  sf::Texture runTexture;
  sf::Texture jumpTexture;
  sf::Texture shieldTexture;
  sf::Sprite sprite; // Sprite animado del jugador (SFML3 requiere textura en ctor)

  enum class AnimState { Idle, Run, Jump, Shield };
  AnimState animState;
  int frameIndex;
  int frameTick;
  bool facingRight;

  sf::Vector2f feetPosition; // Posición del jugador (coordenadas de "pies")

  float velocityY;          // Velocidad vertical (para saltos y gravedad)
  float velocityX;          // Velocidad horizontal (para movimiento lateral)
  bool isJumping;   // Bandera para saber si el jugador está en el aire saltando
  bool isCrouching; // Bandera para saber si el jugador está agachado
  bool moveLeft;  // Bandera de estado: el jugador quiere moverse a la izquierda
  bool moveRight; // Bandera de estado: el jugador quiere moverse a la derecha
  bool jumpHeld;  // Si el jugador está manteniendo presionada la tecla de salto
  bool jumpCutApplied; // Evita aplicar el "cut" más de una vez por salto
  float carryVelocityX; // Velocidad X de la plataforma bajo el jugador

  void setAnimation(AnimState newState);
  void applyFrame();
};