#ifndef _PET_HPP_
#define _PET_HPP_

#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include <boost/sml.hpp>

#include "AnimatedSprite.hpp"

#include "animations.hpp"

// DECLARATION
template <typename T>
class Pet {
    
private:

  std::unique_ptr<Animations> anis;
  
public:

  boost::sml::sm<T> state;

  Pet(Animations*);

};

// IMPLEMENTATION

template <typename T>
Pet<T>::Pet(Animations* rawAnis) : anis(rawAnis) {

}

#endif // _PET_HPP_
