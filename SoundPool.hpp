#include <SFML/Audio.hpp>
#include <queue>
#include <functional>

class SoundPool {
  std::priority_queue<sf::Sound *, std::vector<sf::Sound *>, std::function<bool (sf::Sound *const &s1, sf::Sound *const &s2)>> pool_;
public:
  SoundPool()
    :pool_([](sf::Sound *const &s1, sf::Sound *const &s2) -> bool {
        if (s1->getStatus() == sf::Sound::Paused)
          return true;
        if (s2->getStatus() == sf::Sound::Paused)
          return false;
        return s1->getBuffer()->getDuration() - s1->getPlayingOffset() >
          s2->getBuffer()->getDuration() - s2->getPlayingOffset();
          }) {}
  
  sf::Sound *pop() {
    sf::Sound *sound;
    if (pool_.empty()) {
      return new sf::Sound();
    } else {
      sound = pool_.top();
      if (sound->getStatus() == sf::Sound::Stopped) {
        pool_.pop();
        return sound;
      } else
        return new sf::Sound();
    }
  }

  void push(sf::Sound *sound) {
    pool_.push(sound);
  }
};
