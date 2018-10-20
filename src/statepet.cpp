#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <boost/sml.hpp>

#include "AnimatedSprite.hpp"

#include "animated.hpp"
#include "pet.hpp"

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


using sptrAnim = std::shared_ptr<Animation>;

void loadAnimation (sf::Texture& spriteSheet, std::unordered_map<std::string, sptrAnim>& animMap) {

  sf::Image image;
  if(!image.loadFromFile("assets/doop0.png")) std::cout << "Failed spritesheet file load\n";
  image.createMaskFromColor(sf::Color(255,0,255));

  spriteSheet.loadFromImage(image);

  auto normal = std::make_shared<Animation>();
  normal->setSpriteSheet(spriteSheet);
  for(int i = 0; i < 6; ++i) {
    int left = 32 * i;
    normal->addFrame(sf::IntRect(left, 0, 32, 32));
  }
  
  auto fat = std::make_shared<Animation>();
  fat->setSpriteSheet(spriteSheet);
  for(int i = 0; i < 6; ++i) {
    int left = 32 * i;
    fat->addFrame(sf::IntRect(left, 32, 32 , 32));
  }
  
  auto loved = std::make_shared<Animation>();
  loved->setSpriteSheet(spriteSheet);
  for(int i = 0; i < 6; ++i) {
    int left = 32 * i;
    loved->addFrame(sf::IntRect(left, 64, 32, 32));
  }
  
  animMap["normal"] = normal;
  animMap["fat"] = fat;
  animMap["loved"] = loved;
}

void loadDoop() {

  sf::Image doopImage;
  if (!doopImage.loadFromFile("assets/doop0.png")) std::cout << "Doop spritesheet load failed \n";

  frameInfo doopFrames = {sf::Color(255,0,255), 3, 32, 32,
                          {"normal", "fat", "loved"}, {6, 6, 6}};
  
  Animated doop(doopImage, doopFrames);
}

int main() {
  using namespace sml;

  sm<pet0> sm;

  sf::Vector2i screenSize(640, 480);
  sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "State Test");

  sf::Texture petTex;
  std::unordered_map<std::string, sptrAnim> petAnims;

  auto testPtrMap = std::make_shared<std::unordered_map<std::string, sptrAnim>>();
  
  std::cout << "Loading images\n";
  
  loadAnimation(petTex, petAnims);
  loadAnimation(petTex, *testPtrMap);
  loadDoop();

  std::cout << "Loaded images\n";

  for(auto& x: *testPtrMap) {
      std::cout << x.first << ": " << x.second << std::endl;
  }

  Pet<pet0> pet(std::make_shared<sf::Texture>(petTex), testPtrMap);
  
  AnimatedSprite petSprite(sf::seconds(0.1));
  petSprite.setOrigin(16.0, 16.0);
  petSprite.setScale(sf::Vector2f(4.0,4.0));
  petSprite.setPosition(sf::Vector2f(screenSize / 2));

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

    sptrAnim anim;

    if (pet.state.is("normal"_s)) anim = pet.getAnimation("normal");
    if (pet.state.is("fat"_s)) anim = pet.getAnimation("fat");
    if (pet.state.is("loved"_s)) anim = pet.getAnimation("loved");
    
    sf::Time frameTime = frameClock.restart();
    
    petSprite.play(*anim);
    petSprite.update(frameTime);
    
    // physics

    // rendition
    window.clear();
    window.draw(petSprite);
    window.display();
    
  }
  
  return 0;
}
