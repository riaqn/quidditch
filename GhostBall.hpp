#pragma once

#include "Ball.hpp"

class GhostBall : public Ball {
public:
  GhostBall(Ball &&ball)
    :Ball(std::move(ball)) {}
};

