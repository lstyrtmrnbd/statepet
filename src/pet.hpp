#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include <boost/sml.hpp>

#include "AnimatedSprite.hpp"

template <typename T>
class Pet {

private:

  boost::sml::sm<T> state;

  std::shared_ptr<sf::Texture> spriteSheet;

  std::unordered_map<std::string, Animation> animMap;
  
public:

  Pet();


};
