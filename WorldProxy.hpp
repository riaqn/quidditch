#pragma once
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>

class WorldProxy {
  btSoftRigidDynamicsWorld &world_;
public:
  WorldProxy(btSoftRigidDynamicsWorld &world)
    :world_(world) {}
    
  void add(btRigidBody *const body) {
    world_.addRigidBody(body);
  }

  void add(btSoftBody *const body) {
    world_.addSoftBody(body);
  }

  void add(btRigidBody *const body, short group, short mask) {
    world_.addRigidBody(body, group, mask);
  }

  void remove(btRigidBody *const body) {
    world_.removeRigidBody(body);
  }

  void remove(btSoftBody *const body) {
    world_.removeSoftBody(body);
  }
};

