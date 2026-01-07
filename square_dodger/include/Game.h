#pragma once                 // Directiva para incluir el archivo solo una vez
#include "Obstacle.h"        // Incluye la clase Obstacle
#include "Player.h"          // Incluye la clase Player
#include "PlatformStrip.h"
#include <SFML/Graphics.hpp> // Incluye la biblioteca gráfica de SFML
#include <deque> // Incluye la estructura de datos deque (cola doble)
#include <vector>

class Game { // Definición de la clase Game (Juego principal)
public:
  Game();     // Constructor: configura la ventana y el estado inicial
  void run(); // Método principal que ejecuta el bucle del juego
  void
  resetGame(); // Método para reiniciar el estado del juego (puntos, posiciones)

private:
  void
  processEvents(); // Maneja los eventos de usuario (teclado, cerrar ventana)
  void update();   // Actualiza la lógica del juego (movimiento, colisiones)
  void render();   // Dibuja todos los elementos en la pantalla

  sf::RenderWindow window;        // La ventana del juego
  Player player;                  // El objeto jugador
  std::deque<Obstacle> obstacles; // Lista de obstáculos en pantalla
  int spawnTimer; // Temporizador para controlar cuándo crear nuevos obstáculos

  // Background
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;

  // Tiles / plataformas decorativas
  sf::Texture tilesetTexture;
  std::vector<PlatformStrip> platforms;
  int platformSpawnTimer;
  int groundSpawnTimer;
  int groundNextSpawnDelay;

  // Estado del Juego
  bool isGameOver; // Bandera: ¿Se acabó el juego?
  bool gameWon;    // Bandera: ¿Ganó el jugador?
  int score;       // Puntuación actual

  // Interfaz de Usuario (UI)
  sf::Font font;      // Fuente para el texto
  sf::Text uiText;    // Texto para mensajes (Game Over / Win)
  sf::Text scoreText; // Texto para mostrar la puntuación
};