#pragma once
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>

class WorldProxy {
  btDynamicsWorld &world_;
public:
  WorldProxy(btDynamicsWorld &world)
    :world_(world) {}
    
  void add(btRigidBody *body) {
    world_.addRigidBody(body);
  }

  void add(btRigidBody *body, short group, short mask) {
    world_.addRigidBody(body, group, mask);
  }

  void remove(btRigidBody *body) {
    world_.removeRigidBody(body);
  }
};

