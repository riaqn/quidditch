#pragma  once
#include <iostream>
#include <glm/glm.hpp>

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

extern Log<8> debug;
extern Log<3> error;

template<typename T, glm::precision P>
std::ostream &operator<<(std::ostream &os, const glm::tmat4x4<T, P> &mat) {
  for (auto i = 0; i < 4; ++i) {
    for (auto j = 0; j < 4; ++j) {
      os << mat[i][j] << '\t';
    }
    os << '\n';
  }
  return os;
}
