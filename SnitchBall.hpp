#include "Ball.hpp"

struct SnitchBall : public Ball {
  //seconds to change status
  float countdown;
  
  //are we sleeping?
  bool isSleep;

  //the zone we want to fly in
  glm::vec3 zone_min, zone_max;

  float mu;

  float v0;

  SnitchBall(const Ball &ball, const float countdown,
             const bool isSleep, const glm::vec3 &zone_min,
             const glm::vec3 &zone_max, const float mu,
             const float v0);
};
