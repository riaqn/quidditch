#pragma once
#include <list>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include "Arena.hpp"

class GroupController : public Controller {
public:
  typedef std::vector<btRigidBody *> Group;
protected:
  Group group_;
public:
  virtual void init(WorldProxy &world) {
    world_ = &world;
    for (auto rb : group_)
      world.add(rb);
  }
  
  void add(btRigidBody *const rb) {
  group_.push_back(rb);
}

  const Group &getGroup() {
    return group_;
  }
};
