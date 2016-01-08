#include "Particle.hpp"

bool Particle::action(btRigidBody *const rb,
                      const float elapsed) {
  countdown_ -= elapsed;
  if (countdown_ < 0)
    return false;
  else
    return true;
}
