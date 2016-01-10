#include "Ball.hpp"
#include <random>

class WanderBall : public Ball {
  float v0_;
  float mu_;
public:
  WanderBall(Ball &&ball,
             const float v0, const float mu)
    :Ball(std::move(ball)), v0_(v0), mu_(mu) {}
  
  virtual bool control(const float elapsed);

};
