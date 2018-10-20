#ifndef _ANIMATED_HPP_
#define _ANIMATED_HPP_

#include <memory>
#include <string>
#include <unordered_map>

#include "AnimatedSprite.hpp"
#include "Animation.hpp"

struct frameInfo {

  sf::Color mask;
  int total, width, height;
  std::vector<std::string> names; // length = total
  std::vector<int> counts;        // length = total
};

class Animated {

  using animMap_t = std::unordered_map<std::string, std::unique_ptr<Animation>>;
  
private:

  sf::Texture spriteSheet;
  animMap_t animations;
  AnimatedSprite sprite;
  
public:

  Animated(sf::Image, frameInfo);
  Animation getAnimation(std::string name);
  void loadAnimations(sf::Image baseImage, frameInfo frameDef);
  
};

#endif // _ANIMATED_HPP_
