#pragma once
#include "Controller.hpp"
#include "WorldProxy.hpp"

#include <btBulletDynamicsCommon.h>


#include <list>
#include "Log.hpp"

class Arena {
private:
  btDynamicsWorld &world_;
  WorldProxy proxy_;
  std::list<Controller *> controllers_;
  
public:
  Arena(btDynamicsWorld &world)
    :world_(world),
     proxy_(world)
  {}

  void step(const float elapsed);
  void add(Controller *const controller) {
    controller->init(proxy_);
    controllers_.push_back(controller);
  }
};
