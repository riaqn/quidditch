#include "WanderBall.hpp"
#include "Log.hpp"

WanderBall::WanderBall(const float v0,
                       const float mu)
  :v0(v0), mu(mu) {}

void WanderBall::action(btRigidBody *const rb,
                        const float elapsed) {
  btVector3 v = rb->getLinearVelocity();
  btScalar vl = v.length();
  if (vl == 0)
    v = btVector3(uniform_dist(eng), uniform_dist(eng), uniform_dist(eng));
      
  rb->clearForces();
  btVector3 f1 = v.normalize() * (v0 - vl) * mu;

  rb->applyCentralForce(f1);
}

std::random_device WanderBall::rd;
std::default_random_engine WanderBall::eng;
std::uniform_real_distribution<> WanderBall::uniform_dist(0, 1);
