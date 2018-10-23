#include "visualmanager.hpp"

VisualManager::VisualManager() : images(), textures() {

}

void VisualManager::loadImage(std::string filename, std::string handle) {

  sf::Image image;
  if (!image.loadFromFile(filename)) {

    std::cout << "Failed to load '" << handle
              << "' image from file: " << filename << std::endl;
  }

  this->images.insert(std::make_pair(handle, image));
}

Animations* VisualManager::loadAnimations(std::string handle, frameInfo info) {

  sf::Image& image = images.at(handle);  

  image.createMaskFromColor(info.mask);

  auto tex = std::make_shared<sf::Texture>();
  tex->loadFromImage(image);
  this->textures.insert(std::make_pair(handle, tex));
  
  auto animMap = std::make_unique<animationMap_t>();
  
  for (int i = 0; i < info.total; ++i) {

    auto anim = std::make_unique<Animation>();
    anim->setSpriteSheet(*tex);

    for(int j = 0; j < info.counts.at(i); ++j) {

      int left = info.width * j;
      anim->addFrame(sf::IntRect(left, info.height * i, info.width, info.height));
    }

    animMap->insert(std::make_pair(info.names.at(i), std::move(anim)));
  }

  return new Animations(tex, std::move(animMap));
}


