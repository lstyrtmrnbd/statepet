#ifndef _PET_HPP_
#define _PET_HPP_

#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include <boost/sml.hpp>

#include "AnimatedSprite.hpp"

#include "animations.hpp"

// DECLARATION
template <typename T>
class Pet : public sf::Drawable {
    
private:

  std::shared_ptr<Animations> anis;
  AnimatedSprite sprite;
  
public:

  boost::sml::sm<T> state;

  Pet(Animations*);

  void doSprite(std::function<void(AnimatedSprite&)>);
  void syncAnimationState();
  void update(sf::Time dt);

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

// IMPLEMENTATION

template <typename T>
Pet<T>::Pet(Animations* rawAnis) : anis(rawAnis), state(), sprite() {

}

template <typename T>
void Pet<T>::doSprite(std::function<void(AnimatedSprite&)> fun) {

  fun(this->sprite);
}

template <typename T>
void Pet<T>::syncAnimationState() {

  std::string handle;
  this->state.visit_current_states([&handle](auto state) {
                                     handle = state.c_str();
                                   });

  this->sprite.play(anis->getAnimation(handle));
}

template <typename T>
void Pet<T>::update(sf::Time dt) {
  
  this->sprite.update(dt);
}

template <typename T>
void Pet<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const {

  target.draw(this->sprite);
}

#endif // _PET_HPP_
