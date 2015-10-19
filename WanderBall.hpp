#include "Ball.hpp"

struct WanderBall : public Ball {
  //the speed it wanders
  float v0;

  //percent of delta it coverages, per seconds
  float mu;

  WanderBall(const float m, const float r, const glm::vec3 &pos, const glm::vec3 &v,
             const float v0, const float mu);

};
