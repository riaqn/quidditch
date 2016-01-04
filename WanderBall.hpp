#include "Ball.hpp"
#include <random>

class WanderBall : public Ball {
  
  static std::random_device rd;
  static std::default_random_engine eng;
  static std::uniform_real_distribution<> uniform_dist;

  float v0;
  float mu;
public:
  WanderBall(const float v0, const float mu);
  virtual bool action(btRigidBody *const rb,
                      const float elapsed);
};
