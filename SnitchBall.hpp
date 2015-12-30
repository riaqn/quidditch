#include "Ball.hpp"

class SnitchBall : public Ball {
  //seconds to change status
  float countdown_;
  float time_dormant_, time_active_;
  
  //are we sleeping?
  bool active_;

  //the zone we want to fly in
  btVector3 zone_min_, zone_max_;
  btVector3 mu_;
  float v0_;
  btVector3 v_;

public:
  SnitchBall(const float time_active,
             const float time_dormant,
             const btVector3 &zone_min,
             const btVector3 &zone_max,
             const btVector3 &mu,
             const float v0);

  virtual void action(btRigidBody *const rb, const float elapsed);
};
