#include "utils.hpp"

glm::vec3 convert(const btVector3 &vec) {
  return glm::vec3(vec.x(), vec.y(), vec.z());
}

std::ostream &operator<<(std::ostream &os, const btVector3 &vec) {
  os << '[' << vec.x()
     << ',' << vec.y()
     << ',' << vec.z()
     << ']';
  return os;
}

std::istream &operator >>(std::istream &is, btVector3 &vec) {
  btScalar s;
  is >> s;
  vec.setX(s);
  is >> s;
  vec.setY(s);
  is >> s;
  vec.setZ(s);
  return is;
}


