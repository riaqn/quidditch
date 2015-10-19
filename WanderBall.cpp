#include "WanderBall.hpp"

WanderBall::WanderBall(const float m, const float r, const glm::vec3 &pos, const glm::vec3 &v,
                       const float v0, const float mu)
  :Ball(m, r, pos, v), v0(v0), mu(mu) {}

