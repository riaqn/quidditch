#include "Projection.hpp"
#include <glm/gtc/matrix_transform.hpp>

Projection::Projection(float &&fovy, float &&aspect, float &&zNear, float &&zFar)
  :fovy_(fovy), aspect_(aspect), zNear_(zNear), zFar_(zFar) {
}

glm::mat4 Projection::matrix() const {
  return glm::perspective(fovy_, aspect_, zNear_, zFar_);
}


