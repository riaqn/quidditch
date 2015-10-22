#include "WanderBall.hpp"

WanderBall::WanderBall(const Ball &ball,
                       const float v0, const float mu)
  :Ball(ball), v0(v0), mu(mu) {}

