#include <SFML/Audio.hpp>
#include <queue>
#include <functional>
#include "Log.hpp"

class SoundPool {
  std::priority_queue<sf::Sound *, std::vector<sf::Sound *>, std::function<bool (sf::Sound *const &s1, sf::Sound *const &s2)>> pool_;
public:
  SoundPool();
  
  sf::Sound *pop();
  
  void push(sf::Sound *sound) {
    pool_.push(sound);
  }
};
