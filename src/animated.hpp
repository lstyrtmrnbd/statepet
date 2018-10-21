#ifndef _ANIMATED_HPP_
#define _ANIMATED_HPP_

#include <memory>
#include <string>
#include <unordered_map>

#include "AnimatedSprite.hpp"
#include "Animation.hpp"

#include "common.h"

class Animated {
  
private:

  std::shared_ptr<sf::Texture> spriteSheet;
  std::unique_ptr<animationMap_t> animations;
  AnimatedSprite sprite;
  
public:

  Animated(std::shared_ptr<sf::Texture> spriteSheet, animationMap_t*);
  Animation getAnimation(std::string name);
  void setAnimation(std::string name);
  
};

#endif // _ANIMATED_HPP_
