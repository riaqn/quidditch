#pragma once
#include "Controller.hpp"

class SingleController : public Controller {
public:
  SingleController(const btRigidBody::btRigidBodyConstructionInfo &info)
    :rb_(info) {}
  
  void init(AddCallback cb) {
    cb(&rb_);
  }
  const btRigidBody &getBody() {
    return rb_;
  }
    
protected:
  btRigidBody rb_;
};
