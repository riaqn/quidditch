#include "WanderBall.hpp"
#include "Log.hpp"
#include "utils.hpp"

bool WanderBall::control(const float elapsed) {
  btVector3 v = rb_->getLinearVelocity();
  btScalar vl = v.length();
  if (vl == 0)
    v = btVector3(random<float>(0, 1), random<float>(0, 1), random<float>(0, 1));
      
  rb_->clearForces();
  btVector3 f1 = v.normalize() * (v0_ - vl) * mu_;

  rb_->applyCentralForce(f1);
  return false;
}
