#include "animations.hpp"

Animations::Animations(std::shared_ptr<sf::Texture> sheet,
                       std::unique_ptr<animationMap_t> anims) : spriteSheet(sheet), animations(std::move(anims)) {

}

Animation& Animations::getAnimation(std::string name) {

  return *animations->at(name);
}

