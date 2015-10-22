#include "SnitchBall.hpp"

SnitchBall::SnitchBall(const Ball &ball, const float countdown,
                       const bool isSleep, const glm::vec3 &zone_min,
                       const glm::vec3 &zone_max, const float mu,
                       const float v0)
  :Ball(ball), countdown(countdown), isSleep(isSleep), zone_min(zone_min), zone_max(zone_max), mu(mu), v0(v0) {
}
