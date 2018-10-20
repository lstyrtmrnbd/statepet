#include "pet.hpp"

template <typename T>
Pet<T>::Pet(std::shared_ptr<sf::Texture> spriteSheet,
            std::unordered_map<std::string, sptrAnim> animMap) : state(boost::sml::sm<T>()), spriteSheet(spriteSheet), animMap(animMap) {

}
