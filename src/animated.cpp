#include "animated.hpp"

Animated::Animated(std::shared_ptr<sf::Texture> sheet, animationMap_t* anims) : spriteSheet(sheet), animations(anims) {

}

Animation Animated::getAnimation(std::string name) {

  return *animations->at(name);
}

