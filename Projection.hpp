#pragma once
#include <glm/glm.hpp>

class Projection {
public:
  Projection(float &&fovy, float &&aspect, float &&zNear, float &&zFar);
  glm::mat4 matrix() const ;
private:
  float fovy_, aspect_, zNear_, zFar_;
};
