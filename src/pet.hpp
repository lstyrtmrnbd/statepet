#ifndef _PET_HPP_
#define _PET_HPP_

#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include <boost/sml.hpp>

#include "AnimatedSprite.hpp"

#include "animated.hpp"

using sptrAnim = std::shared_ptr<Animation>;
using mapType = std::shared_ptr<std::unordered_map<std::string, sptrAnim>>;

// DECLARATION
template <typename T>
class Pet {
    
private:

  std::shared_ptr<sf::Texture> spriteSheet;
  mapType animMap;
  AnimatedSprite sprite; // inherit this from 'animated' class,
                         // as well as method to load it given frames struct 
  
public:

  boost::sml::sm<T> state;

  Pet(std::shared_ptr<sf::Texture> spriteSheet,
      mapType animMap);

  sptrAnim getAnimation(std::string name);

};

// IMPLEMENTATION

template <typename T>
Pet<T>::Pet(std::shared_ptr<sf::Texture> spriteSheet,
            mapType animMap) : state(boost::sml::sm<T>()), spriteSheet(spriteSheet), animMap(animMap) {

}

template<typename T>
sptrAnim Pet<T>::getAnimation(std::string name) {

  return this->animMap->at(name);
}

#endif // _PET_HPP_
