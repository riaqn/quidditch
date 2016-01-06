#pragma once

#include "Ball.hpp"

class GhostBall : public Ball {
public:
  GhostBall(const Ball &ball)
    :Ball(ball) {}
};

