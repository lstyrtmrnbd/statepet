#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <boost/sml.hpp>

#include "AnimatedSprite.hpp"

#include "animations.hpp"
#include "pet.hpp"
#include "visualmanager.hpp"

namespace sml = boost::sml;

struct fatten {};
struct love {};
  
struct pet0 {
  auto operator()() const {
    using namespace sml;
    return make_transition_table (
                                  *"normal"_s + event<fatten> = "fat"_s,
                                  "fat"_s + event<fatten> = "normal"_s,
                                  "normal"_s + event<love> = "loved"_s,
                                  "loved"_s + event<love> = "normal"_s
                                  );
  }
};

int main() {
  
  sf::Vector2i screenSize(640, 480);
  sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "State Test");

  auto visman = std::make_unique<VisualManager>();
  
  visman->loadImage("assets/doop0.png", "doop");

  frameInfo doopFrames = {3, 32, 32,
                          {"normal", "fat", "loved"},
                          {6, 6, 6},
                          sf::Color(255,0,255)};
  
  Pet<pet0> pet(visman->loadAnimations("doop", doopFrames));

  pet.doSprite([screenSize](AnimatedSprite& sprite){
                 sprite.setFrameTime(sf::seconds(0.1));
                 sprite.setOrigin(16.0, 16.0);
                 sprite.setScale(sf::Vector2f(4.0,4.0));
                 sprite.setPosition(sf::Vector2f(screenSize / 2));
               });

  sf::Clock frameClock = sf::Clock();

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {

      // NEED INPUT HANDLER
      
      if (event.type == sf::Event::KeyPressed) {

        if (event.key.code == sf::Keyboard::Space) pet.state.process_event(fatten{});
        if (event.key.code == sf::Keyboard::L) pet.state.process_event(love{});

        if (event.key.code == sf::Keyboard::Escape) window.close();
      }
      
      if (event.type == sf::Event::Closed) window.close();
    }

    sf::Time frameTime = frameClock.restart();
        
    pet.syncAnimationState();
    pet.update(frameTime);
    
    // physics

    // rendition
    window.clear();
    window.draw(pet);
    window.display();
    
  }
  
  return 0;
}
