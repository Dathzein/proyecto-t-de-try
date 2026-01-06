#include "PlatformStrip.h"
#include <algorithm>

namespace {
constexpr int kTileSize = 32;
constexpr int kTilesetColumns = 17; // Tileset.png: 544px / 32px = 17 columnas
} // namespace

sf::IntRect PlatformStrip::tileRect(int tileId) {
  int col = tileId % kTilesetColumns;
  int row = tileId / kTilesetColumns;
  return sf::IntRect({col * kTileSize, row * kTileSize}, {kTileSize, kTileSize});
}

PlatformStrip::PlatformStrip(const sf::Texture &tilesetTexture, int leftTileId,
                             int midTileId, int rightTileId, int lengthTiles,
                             sf::Vector2f topLeft, float speedX)
    : tileset(&tilesetTexture), velocityX(speedX) {
  if (lengthTiles < 1)
    lengthTiles = 1;

  sprites.reserve(static_cast<size_t>(lengthTiles));

  for (int i = 0; i < lengthTiles; i++) {
    int tileId = midTileId;
    if (lengthTiles == 1) {
      tileId = midTileId;
    } else if (i == 0) {
      tileId = leftTileId;
    } else if (i == lengthTiles - 1) {
      tileId = rightTileId;
    }

    sf::Sprite s(*tileset);
    s.setTextureRect(tileRect(tileId));
    s.setPosition({topLeft.x + static_cast<float>(i * kTileSize), topLeft.y});
    sprites.push_back(s);
  }
}

void PlatformStrip::update() {
  for (auto &s : sprites) {
    s.move({velocityX, 0.f});
  }
}

void PlatformStrip::draw(sf::RenderTarget &target) const {
  for (const auto &s : sprites) {
    target.draw(s);
  }
}

bool PlatformStrip::isOffscreen(float leftBoundX) const {
  float rightmost = -1e9f;
  for (const auto &s : sprites) {
    rightmost = std::max(rightmost, s.getPosition().x + kTileSize);
  }
  return rightmost < leftBoundX;
}


