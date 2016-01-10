#pragma once
#include "Arena.hpp"
#include <memory>

class SingleController : public Controller {
public:
  SingleController(const btRigidBody::btRigidBodyConstructionInfo &info)
    :rb_(new btRigidBody(info)) {
    rb_->setUserPointer(this);
  }

  SingleController(SingleController &&sc)
    :rb_(std::move(sc.rb_)) {
    rb_->setUserPointer(this);
  }
  
  void init(WorldProxy &world) {
    world.add(rb_.get());
  }
  
  const btRigidBody &getBody() {
    return *rb_;
  }
  
  ~SingleController() {
  }
    
protected:
  std::unique_ptr<btRigidBody> rb_;
};
