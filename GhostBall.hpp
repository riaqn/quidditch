#include "Ball.hpp"

class GhostBall : public Ball {
public:
  GhostBall(float m, float r, const glm::vec3 &pos, const glm::vec3 &v);
};
