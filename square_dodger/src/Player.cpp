#include "Player.h" // Incluye el encabezado de la clase Player
#include <iostream>

// Constructor de la clase Player
Player::Player() : sprite(idleTexture) {
  // Carga de texturas (spritesheet por animación)
  if (!idleTexture.loadFromFile("assets/sprites/fighter/Idle.png")) {
    std::cerr << "Failed to load Fighter Idle.png" << std::endl;
  }
  if (!runTexture.loadFromFile("assets/sprites/fighter/Run.png")) {
    std::cerr << "Failed to load Fighter Run.png" << std::endl;
  }
  if (!jumpTexture.loadFromFile("assets/sprites/fighter/Jump.png")) {
    std::cerr << "Failed to load Fighter Jump.png" << std::endl;
  }
  if (!shieldTexture.loadFromFile("assets/sprites/fighter/Shield.png")) {
    std::cerr << "Failed to load Fighter Shield.png" << std::endl;
  }

  // Posición inicial: usamos coordenada de "pies" para mantener el contacto con
  // el suelo constante. Con el piso de tiles (32px), usamos y=308 para que los
  // pies queden sobre el borde superior del tile.
  feetPosition = {100.f, 308.f};

  velocityY = 0;                      // Inicializa la velocidad vertical en 0
  velocityX = 0;                      // Inicializa la velocidad horizontal en 0
  isJumping = false;                  // No está saltando inicialmente
  isCrouching = false;                // No está agachado inicialmente
  moveLeft = false;                   // No se está moviendo a la izquierda
  moveRight = false;                  // No se está moviendo a la derecha
  jumpHeld = false;
  jumpCutApplied = false;

  animState = AnimState::Idle;
  frameIndex = 0;
  frameTick = 0;
  facingRight = true;

  sprite.setTexture(idleTexture);
  applyFrame();
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
      }
    } else {                     // Si se suelta 'Q'
      if (isCrouching) {         // Y estaba agachado
        isCrouching = false;     // Marca estado de pie
      }
    }
  } else if (key ==
             sf::Keyboard::Key::Space) { // Si la tecla es Espacio (Saltar)
    // Salto variable tipo Hollow Knight:
    // - Al presionar: inicia salto con la misma fuerza máxima de siempre.
    // - Al soltar rápido durante la subida: recorta la velocidad vertical para
    //   lograr un salto más bajo.
    if (isPressed) {
      jumpHeld = true;
      // Si se presiona, no está ya saltando y no está agachado
      if (!isJumping && !isCrouching) {
        velocityY = -12;  // Fuerza máxima (se mantiene la altura máxima actual)
        isJumping = true; // Marca estado saltando
        jumpCutApplied = false;
      }
    } else {
      jumpHeld = false;
      // Si soltó en subida, aplica "jump cut" una sola vez
      if (isJumping && velocityY < 0.f && !jumpCutApplied) {
        velocityY *= 0.35f; // mientras más chico, más "corto" el salto
        jumpCutApplied = true;
      }
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

  feetPosition.x += velocityX;

  // Límites de pantalla (0 a 800 de ancho)
  // Antes: x en [0, 760] para un rectángulo de 40px de ancho.
  // Ahora: feetPosition.x representa el centro aproximado del jugador.
  if (feetPosition.x < 20.f)
    feetPosition.x = 20.f;
  if (feetPosition.x > 780.f)
    feetPosition.x = 780.f;

  velocityY += 0.5f;          // Aplica gravedad (aumenta velocidad hacia abajo)
  feetPosition.y += velocityY;

  // Colisión con el suelo
  float groundFeetY = 308.0f; // pies siempre en el mismo suelo (piso de tiles)

  // Si la posición Y supera el suelo
  if (feetPosition.y >= groundFeetY) {
    feetPosition.y = groundFeetY; // Fija la posición en el suelo
    velocityY = 0;                         // Detiene la caída
    isJumping = false;                     // Permite volver a saltar
    jumpCutApplied = false;
  }

  // Dirección (flip) y selección de animación
  if (velocityX < 0)
    facingRight = false;
  else if (velocityX > 0)
    facingRight = true;

  AnimState desired =
      isJumping ? AnimState::Jump
                : (isCrouching ? AnimState::Shield
                               : ((velocityX != 0) ? AnimState::Run
                                                   : AnimState::Idle));
  setAnimation(desired);

  // Avanza frames en base a ticks (la ventana está limitada a 60fps)
  frameTick++;
  int delay = 10; // default Idle
  int frames = 1;
  const sf::Texture *tex = &idleTexture;
  switch (animState) {
  case AnimState::Idle:
    delay = 10;
    frames = 6;
    tex = &idleTexture;
    break;
  case AnimState::Run:
    delay = 5;
    frames = 8;
    tex = &runTexture;
    break;
  case AnimState::Jump:
    delay = 6;
    frames = 10;
    tex = &jumpTexture;
    break;
  case AnimState::Shield:
    delay = 10;
    frames = 2; // Shield.png en este pack tiene 2 frames (se ve como guardia)
    tex = &shieldTexture;
    break;
  }

  if (frameTick >= delay) {
    frameTick = 0;
    frameIndex = (frameIndex + 1) % frames;
    sprite.setTexture(*tex);
    applyFrame();
  } else {
    // Asegura posición/flip aunque no cambie el frame
    applyFrame();
  }
}

const sf::Sprite &Player::getSprite() const { return sprite; }

sf::FloatRect Player::getBounds() {
  // Mantiene hitbox similar al cuadrado original (40x40), con versión agachado
  // 40x20, usando feetPosition como referencia.
  float w = 40.f;
  float h = isCrouching ? 20.f : 40.f;
  return sf::FloatRect({feetPosition.x - w / 2.f, feetPosition.y - h}, {w, h});
} // Retorna el rectángulo de colisión

void Player::setAnimation(AnimState newState) {
  if (newState == animState)
    return;
  animState = newState;
  frameIndex = 0;
  frameTick = 0;
}

void Player::applyFrame() {
  const sf::Texture *tex = &idleTexture;
  int frames = 6;
  switch (animState) {
  case AnimState::Idle:
    tex = &idleTexture;
    frames = 6;
    break;
  case AnimState::Run:
    tex = &runTexture;
    frames = 8;
    break;
  case AnimState::Jump:
    tex = &jumpTexture;
    frames = 10;
    break;
  case AnimState::Shield:
    tex = &shieldTexture;
    frames = 2;
    break;
  }

  sprite.setTexture(*tex);

  // Calcula tamaño de frame a partir del ancho total / cantidad de frames
  auto texSize = tex->getSize();
  int frameW = (frames > 0) ? static_cast<int>(texSize.x / frames)
                            : static_cast<int>(texSize.x);
  int frameH = static_cast<int>(texSize.y);

  sprite.setTextureRect(
      sf::IntRect({frameW * frameIndex, 0}, {frameW, frameH}));

  // Origen en el "suelo" del sprite para que los pies queden alineados
  sprite.setOrigin({frameW / 2.f, static_cast<float>(frameH)});

  // Escala: ajusta altura visual (la hitbox se mantiene 40x40 / 40x20)
  float targetHeight = isCrouching ? 45.f : 60.f;
  float scale = (frameH > 0) ? (targetHeight / static_cast<float>(frameH)) : 1.f;
  sprite.setScale({facingRight ? scale : -scale, scale});

  sprite.setPosition(feetPosition);
}