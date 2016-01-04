#include "GhostBall.hpp"
#include <glm/glm.hpp>

class CueBall : public Ball {
private:
  float userPower_;
  float maxForce_;
public:
  btVector3 dir;
  CueBall(const float userPower,
          const float maxForce)
    :userPower_(userPower), maxForce_(maxForce) {};
  virtual bool action(btRigidBody *const rb,
                      const float elapsed);
};
