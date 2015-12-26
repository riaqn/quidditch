#include "Ball.hpp"

struct WanderBall : public Ball {
  float k;
  float v0;
  float mu;

  WanderBall(const float k, const float v0, const float mu);
};
