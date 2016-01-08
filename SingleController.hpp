#pragma once
#include "Controller.hpp"
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
  
  void init(AddCallback cb) {
    cb(rb_.get(), btBroadphaseProxy::AllFilter, btBroadphaseProxy::AllFilter);
  }
  
  const btRigidBody &getBody() {
    return *rb_;
  }
  
  ~SingleController() {
  }
    
protected:
  std::unique_ptr<btRigidBody> rb_;
};
