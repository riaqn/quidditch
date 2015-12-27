#pragma once
#include <LinearMath/btVector3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <istream>

glm::vec3 convert(const btVector3 &vec);
btVector3 convert(const glm::vec3 &vec);

template<typename T, glm::precision P>
std::istream &operator >>(std::istream &is, glm::tvec3<T, P> &vec) {
  is >> vec[0] >> vec[1] >> vec[2];
  return is;
}


template<typename T, glm::precision P>
std::ostream &operator <<(std::ostream &is, const glm::tvec3<T, P> &vec) {
  is << glm::to_string(vec);
  return is;
}

template<typename T, glm::precision P>
std::ostream &operator <<(std::ostream &is, const glm::tvec2<T, P> &vec) {
  is << glm::to_string(vec);
  return is;
}

template<typename T, glm::precision P>
std::ostream &operator<<(std::ostream &os, const glm::tmat4x4<T, P> &mat) {
  os << glm::to_string(mat);
  return os;
}


std::ostream &operator<<(std::ostream &os, const btVector3 &vec);
std::istream &operator >>(std::istream &is, btVector3 &vec);
