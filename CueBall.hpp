#include "Ball.hpp"
#include <glm/glm.hpp>

class CueBall : public Ball {
private:
  float userPower_;
  float maxForce_;
  float fantasy_;
public:
  btVector3 dir;
  CueBall(Ball &&ball,
          const float userPower,
          const float maxForce)
    :Ball(std::move(ball)), userPower_(userPower), maxForce_(maxForce) {};

  void setFantasy(const float fantasy) {
    fantasy_ = fantasy;
  }
  
  virtual bool control(const float elapsed);
};
