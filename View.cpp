#include "View.hpp"
#include <glm/gtc/matrix_transform.hpp>

View::View(glm::vec3 &&eye, glm::vec3 &&center, glm::vec3 &&up)
  :eye_(eye), center_(center), up_(up) {
}

glm::mat4 View::matrix() const {
  return glm::lookAt(eye_, center_, up_);
}
