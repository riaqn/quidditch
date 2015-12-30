#pragma once

#include "Ball.hpp"

class GhostBall : public Ball {
public:
  GhostBall() {}
  virtual void action(btRigidBody *rb, const float elapsed) {}
};

