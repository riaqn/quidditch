#include "Ball.hpp"
#include <random>

class WanderBall : public Ball {
  
  static std::random_device rd;
  static std::default_random_engine eng;
  static std::uniform_real_distribution<> uniform_dist;

  float v0_;
  float mu_;
public:
  WanderBall(const btRigidBody::btRigidBodyConstructionInfo &info,
             const float v0, const float mu)
    :Ball(info), v0_(v0), mu_(mu) {}
  
  virtual bool control(const float elapsed,
                       RemoveCallback cb);
};
