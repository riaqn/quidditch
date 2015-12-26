#pragma  once
#include <iostream>
#include <glm/glm.hpp>
#include "utils.hpp"

#define LOG_LEVEL 8

template<int level>
class Log {
public:
  template<typename T>
  Log &operator<<(const T &t);
};

template<int level>
template<typename T>
Log<level> &Log<level>::operator<<(const T &t) {
  if (level < LOG_LEVEL)
    std::cerr << t;
  return *this;
}

extern Log<7> debug;
extern Log<3> error;
extern Log<5> notice;

