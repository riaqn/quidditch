#pragma once

#include <glm/glm.hpp>

class View {
public:
  View(const glm::vec3 &eye, const glm::vec2 &angle);
  void moveUp(const float d);
  void moveRight(const float d);
  void turn(const glm::vec2 &d);
  void zoom(const float d);
  glm::mat4 matrix() const ;
  glm::vec3 eye;
  glm::vec2 angle;
  glm::vec3 direction, right, up;
};
