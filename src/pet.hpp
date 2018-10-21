#ifndef _PET_HPP_
#define _PET_HPP_

#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include <boost/sml.hpp>

#include "AnimatedSprite.hpp"

#include "animated.hpp"

// DECLARATION
template <typename T>
class Pet {
    
private:

  Animated ani;
  
public:

  boost::sml::sm<T> state;

  Pet();

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
