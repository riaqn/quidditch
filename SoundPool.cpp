#include "SoundPool.hpp"
#include <limits>

SoundPool::SoundPool()
    :pool_([](sf::Sound *const &s1, sf::Sound *const &s2) -> bool {
        float t1, t2;
        
        if (s1->getStatus() == sf::Sound::Paused)
          t1 = std::numeric_limits<float>::max();
        else if (s1->getStatus() == sf::Sound::Stopped) {
          //debug << "Stoppped!\n";
          t1 = 0;
        } else
          t1 = (s1->getBuffer()->getDuration() - s1->getPlayingOffset()).asSeconds();
        
        if (s2->getStatus() == sf::Sound::Paused)
          t2 = std::numeric_limits<float>::max();
        else if (s2->getStatus() == sf::Sound::Stopped) {
          //debug << "Stoppped!\n";
          t2 = 0;
        } else
          t2 = (s2->getBuffer()->getDuration() - s2->getPlayingOffset()).asSeconds();
        
        return t1 > t2;
      }) {}

sf::Sound *SoundPool::pop() {
  sf::Sound *sound;
  if (pool_.empty()) {
    return new sf::Sound();
  } else {
    sound = pool_.top();
    if (sound->getStatus() == sf::Sound::Stopped) {
      pool_.pop();
      return sound;
    } else {
      static int count = 0 ;
      debug << count ++ << "allocating new\n";
      return new sf::Sound();
    }
  }
  }
