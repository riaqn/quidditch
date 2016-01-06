#pragma once
#include "Controller.hpp"
#include <btBulletDynamicsCommon.h>

#include <set>

class Arena {
  btDynamicsWorld &world_;
  std::set<Controller *> controllers_;
  Controller::RemoveCallback remove_;
  Controller::AddCallback add_;
public:
  Arena(btDynamicsWorld &world)
    :world_(world), remove_([this](btRigidBody *const rb) -> void {
        this->world_.removeRigidBody(rb);
      }), add_([this](btRigidBody *const rb) -> void {
          this->world_.addRigidBody(rb);
        }) {}

  void step(const float elapsed);
  void add(Controller *const controller) {
    controller->init(add_);
    controllers_.insert(controller);
  }
};
