#pragma once
#include <functional>
#include "WorldProxy.hpp"

class Controller {
public:
  typedef std::function<void ()> DestroyCallback;

private:
  DestroyCallback cb_;
protected:
  WorldProxy *world_;

public:
  virtual void init(WorldProxy &world) {
    world_ = &world;
  }
  
  virtual bool control(const float elapsed) {
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
