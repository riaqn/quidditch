#pragma once
#include <list>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include "Controller.hpp"

class GroupController : public Controller {
public:
  typedef std::list<btRigidBody *> Group;
protected:
  Group group_;
public:
  virtual bool control(const float elapsed,
                       RemoveCallback cb) = 0;

  virtual void init(AddCallback cb) {
    for (auto rb : group_)
      cb(rb, btBroadphaseProxy::AllFilter, btBroadphaseProxy::AllFilter);
  }
  
  void add(btRigidBody *const rb) {
  group_.push_back(rb);
}

  const Group &getGroup() {
    return group_;
  }
};
