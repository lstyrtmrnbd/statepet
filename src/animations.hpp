#ifndef _ANIMATIONS_HPP_
#define _ANIMATIONS_HPP_

#include <memory>
#include <string>
#include <unordered_map>

#include "AnimatedSprite.hpp"
#include "Animation.hpp"

#include "common.h"

class Animations {
  
private:

  std::shared_ptr<sf::Texture> spriteSheet;
  std::unique_ptr<animationMap_t> animations;
  AnimatedSprite sprite;
  
public:

  Animations(std::shared_ptr<sf::Texture> sheet,
             std::unique_ptr<animationMap_t> anims);
  Animation& getAnimation(std::string name);
  void setAnimation(std::string name);
  
};

#endif // _ANIMATIONS_HPP_
