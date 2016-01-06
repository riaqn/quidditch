#include "Ball.hpp"
#include <glm/glm.hpp>

class CueBall : public Ball {
private:
  float userPower_;
  float maxForce_;
public:
  btVector3 dir;
  CueBall(const Ball &ball,
          const float userPower,
          const float maxForce)
    :Ball(ball), userPower_(userPower), maxForce_(maxForce) {};
  virtual bool control(const float elapsed,
                       RemoveCallback cb);
};
