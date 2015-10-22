#include "Ball.hpp"

Ball::Ball(float m, float r, const glm::vec3 &x, const glm::vec3 &v, const std::string &name)
  :m(m), r(r), x(x), v(v), name(name) {}
