#include "CueBall.hpp"

bool CueBall::action(btRigidBody *const rb,
                     const float elapsed) {
  btVector3 v = rb->getLinearVelocity();
  float v0 = v.dot(dir);

  float f;
  if (v0 == 0) {
    f = maxForce_;
  } else {
    f = userPower_ / v0;
    if (f < 0 || f > maxForce_)
      f = maxForce_;
  }
  rb->clearForces();
  rb->applyCentralForce(f * dir);
  rb->activate();
  return true;
}
