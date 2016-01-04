#pragma once
#include <BulletDynamics/Dynamics/btRigidBody.h>
class Body {
public:
  virtual bool action(btRigidBody *const rb,
                      const float elapsed) {
    return true;
  }
};
