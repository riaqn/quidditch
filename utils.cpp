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

std::random_device dev;
std::default_random_engine eng;
std::uniform_real_distribution<float> dist_float(0, 1);

template<>
float random(const float &a, const float &b) {
  return dist_float(eng) * (b - a) + a;
}

template<>
btVector3 random(const btVector3 &a, const btVector3 &b) {
  return btVector3(random(a.x(), b.x()),
                   random(a.y(), b.y()),
                   random(a.z(), b.z()));
}
