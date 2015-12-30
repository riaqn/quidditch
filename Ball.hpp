#pragma once
#include <BulletDynamics/Dynamics/btRigidBody.h>

class Ball {
public:
  virtual void action(btRigidBody *const rb,
                      const float elapsed) = 0;
};
