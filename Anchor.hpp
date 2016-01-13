#include "SingleController.hpp"

class Anchor : public SingleController {
  btSphereShape shape_;
  btDefaultMotionState ms_;
  btVector3 localInertia;
public:
  Anchor(const btVector3 &pos)
    :ms_(btTransform(btQuaternion(0, 0, 0, 1), pos)),
     shape_(0.001) {
    rb_.reset(new btRigidBody(0, &ms_, &shape_));
  }

};
