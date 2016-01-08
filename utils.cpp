#include "utils.hpp"

template <>
btVector3 convert(const glm::vec3 &from) {
  return btVector3(from.x, from.y, from.z);
}

template <>
glm::vec3 convert(const btVector3 &from) {
  return glm::vec3(from.x(), from.y(), from.z());
}

template <>
sf::Vector3f convert(const glm::vec3 &from) {
  return sf::Vector3f(from.x, from.y, from.z);
}

template <>
sf::Vector3f convert(const btVector3 &from) {
  return convert<sf::Vector3f>(convert<glm::vec3>(from));
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


