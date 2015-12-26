#include "utils.hpp"

glm::vec3 convert(const btVector3 &vec) {
  return glm::vec3(vec.x(), vec.y(), vec.z());
}
