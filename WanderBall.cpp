#include "WanderBall.hpp"
#include "Log.hpp"

bool WanderBall::control(const float elapsed,
                         RemoveCallback cb) {
  btVector3 v = rb_.getLinearVelocity();
  btScalar vl = v.length();
  if (vl == 0)
    v = btVector3(uniform_dist(eng), uniform_dist(eng), uniform_dist(eng));
      
  rb_.clearForces();
  btVector3 f1 = v.normalize() * (v0_ - vl) * mu_;

  rb_.applyCentralForce(f1);
  return false;
}

std::random_device WanderBall::rd;
std::default_random_engine WanderBall::eng;
std::uniform_real_distribution<> WanderBall::uniform_dist(0, 1);
