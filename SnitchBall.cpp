#include "SnitchBall.hpp"

#include "Log.hpp"

SnitchBall::SnitchBall(const float time_active,
                       const float time_dormant,
                       const btVector3 &zone_min,
                       const btVector3 &zone_max,
                       const btVector3 &mu,
                       const float v0)
  :time_active_(time_active),
   time_dormant_(time_dormant),
   zone_min_(zone_min),
   zone_max_(zone_max),
   mu_(mu),
   v0_(v0),
   active_(false),
   countdown_(time_dormant) {}

bool SnitchBall::action(btRigidBody *const rb,
                        const float elapsed) {
  if (active_) {
    countdown_ -= elapsed;
    if (countdown_ < 0) {
      debug << "enter dormant\n";
      active_ = false;
      countdown_ = time_dormant_;
    }
    
    const btVector3 &p = rb->getWorldTransform().getOrigin();
    
    if (p.x() < zone_min_.x())
      v_ += btVector3(1, 0, 0) * mu_ * elapsed;
    else if (p.x() > zone_max_.x())
      v_ += btVector3(-1, 0, 0) * mu_ * elapsed;
    
    if (p.y() < zone_min_.y())
      v_ += btVector3(0, 1, 0) * mu_ * elapsed;
    else if (p.y() > zone_max_.y())
      v_ += btVector3(0, -1, 0) * mu_ * elapsed;
    
    if (p.z() < zone_min_.z())
      v_ += btVector3(0, 0, 1) * mu_ * elapsed;
    else if (p.z() > zone_max_.z())
      v_ += btVector3(0, 0, -1) * mu_ * elapsed;


    if (v_.length() > v0_)
      v_ *= v0_ / v_.length();
    rb->setLinearVelocity(v_);
    rb->activate();
  } else {
    countdown_ -= elapsed;
    if (countdown_ < 0) {
      debug << "enter acitve\n";
      active_ = true;
      countdown_ = time_active_;
      v_ = rb->getLinearVelocity();
    }
  }
  return true;
}
