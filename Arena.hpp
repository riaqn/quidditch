#pragma once
#include "Controller.hpp"
#include <btBulletDynamicsCommon.h>

#include <list>
#include "Log.hpp"

class Arena {
  btDynamicsWorld &world_;
  std::list<Controller *> controllers_;
  Controller::RemoveCallback remove_;
  Controller::AddCallback add_;
public:
  Arena(btDynamicsWorld &world)
    :world_(world), remove_([this](btRigidBody *const rb) -> void {
        debug << "world.removeRigidBody()" << rb << '\n';
        this->world_.removeRigidBody(rb);
      }), add_([this](btRigidBody *const rb, short group, short mask) -> void {
          debug << "world.addRigidBody()" << rb << '\n';
          this->world_.addRigidBody(rb, group, mask);
        }) {}

  void step(const float elapsed);
  void add(Controller *const controller) {
    controller->init(add_);
    controllers_.push_back(controller);
  }
};
