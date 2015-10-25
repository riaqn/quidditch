#include <vector>
#include "Ball.hpp"
#include "Wall.hpp"

class Arena {
private:
  std::vector<Ball *> balls_;
  std::vector<Wall *> walls_;
  const glm::vec3 g = glm::vec3(0, -9.8, 0);
  const float mu = 0.01;

  bool onGround(const Ball *ball) const ;
public:
  unsigned score = 0;
  //everything in the universe is destined
  void deduce(const float t);
  void attach(Ball *ball);
  void attach(Wall *wall);
};
