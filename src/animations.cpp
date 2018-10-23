#include "animations.hpp"

Animations::Animations(std::shared_ptr<sf::Texture> sheet, animationMap_t* anims) : spriteSheet(sheet), animations(anims) {

}

Animation Animations::getAnimation(std::string name) {

  return *animations->at(name);
}

