#pragma once
#include <functional>
#include <BulletDynamics/Dynamics/btRigidBody.h>

class Controller {
public:
  typedef std::function<void (btRigidBody *const, short group, short mask)> AddCallback;
  typedef std::function<void (btRigidBody *const)> RemoveCallback;
  typedef std::function<void ()> DestroyCallback;
private:
  DestroyCallback cb_;

public:
  virtual void init(AddCallback cb) = 0;
  virtual bool control(const float elapsed,
                       RemoveCallback cb) {
    return false;
  }
  
  ~Controller() {
    if (cb_)
      cb_();
  }
  
  void setDestroyCallback(const DestroyCallback cb) {
    cb_ = cb;
  }

  DestroyCallback getDestroyCallback() {
    return cb_;
  }
};
