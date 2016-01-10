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
  SnitchBall(Ball &&ball,
             const float time_active,
             const float time_dormant,
             const btVector3 &zone_min,
             const btVector3 &zone_max,
             const btVector3 &mu,
             const float v0)
    :Ball(std::move(ball)),
     time_active_(time_active),
     time_dormant_(time_dormant),
     zone_min_(zone_min),
     zone_max_(zone_max),
     mu_(mu),
     v0_(v0),
     active_(false),
     countdown_(time_dormant) {}

  virtual bool control(const float elapsed);
};
