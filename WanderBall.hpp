#include "Ball.hpp"

struct WanderBall : public Ball {
  //the speed it wanders
  float v0;

  //percent of delta it coverages, per seconds
  float mu;

  WanderBall(const Ball &ball, const float v0, const float mu);
};
