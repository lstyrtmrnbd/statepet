#ifndef _VISUALMANAGER_HPP_
#define _VISUALMANAGER_HPP_

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "common.h"
#include "animations.hpp"

struct frameInfo {

  int total, width, height;
  std::vector<std::string> names; // length = total
  std::vector<int> counts;        // length = total
  sf::Color mask;
};

class VisualManager {

private:

  std::unordered_map<std::string, sf::Image> images;
  std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
  
public:

  VisualManager();
  void loadImage(std::string filename, std::string handle);
  Animations* loadAnimations(std::string handle, frameInfo info);
};

#endif // _VISUAL_MANAGER_HPP_
