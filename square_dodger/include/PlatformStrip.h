#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Un "strip" horizontal de tiles (32x32) recortados desde Tileset.png
// Se mueve de derecha a izquierda a una velocidad configurable.
class PlatformStrip {
public:
  PlatformStrip(const sf::Texture &tilesetTexture, int leftTileId, int midTileId,
                int rightTileId, int lengthTiles, sf::Vector2f topLeft,
                float speedX);

  void update();
  void draw(sf::RenderTarget &target) const;
  bool isOffscreen(float leftBoundX) const;

private:
  const sf::Texture *tileset;
  std::vector<sf::Sprite> sprites;
  float velocityX;

  static sf::IntRect tileRect(int tileId);
};


