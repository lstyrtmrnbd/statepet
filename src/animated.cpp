#include "animated.hpp"

Animation Animated::getAnimation(std::string name) {

  return *animations.at(name);
}

void Animated::loadAnimations(sf::Image baseImage, frameInfo frameDef) {

  baseImage.createMaskFromColor(frameDef.mask);
  this->spriteSheet.loadFromImage(baseImage);
  
  this->animations = animMap_t();
  
  for (int i = 0; i < frameDef.total; ++i) {

    auto anim = std::make_unique<Animation>();
    anim->setSpriteSheet(this->spriteSheet);

    for(int j = 0; j < frameDef.counts.at(i); ++j) {

      int left = frameDef.width * j;
      anim->addFrame(sf::IntRect(left, frameDef.height * i, frameDef.width, frameDef.height));
    }

    this->animations.insert(std::make_pair(frameDef.names.at(i), std::move(anim)));
  }
}

Animated::Animated(sf::Image baseImage, frameInfo frameDef) {

  loadAnimations(baseImage, frameDef);
}
