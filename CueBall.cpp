#include "CueBall.hpp"
#include "Log.hpp"

bool CueBall::control(const float elapsed,
                      RemoveCallback cb) {
    
  btVector3 v = rb_->getLinearVelocity();
  float v0 = v.dot(dir);

  float f;
  if (v0 == 0) {
    f = maxForce_;
  } else {
    f = userPower_ / v0;
    if (f < 0 || f > maxForce_)
      f = maxForce_;
  }
  
  if (fantasy_ > 0) {
    fantasy_ -= elapsed;
    f = -f;
  }

  rb_->clearForces();
  rb_->applyCentralForce(f * dir);
  rb_->activate();
  return false;
}
