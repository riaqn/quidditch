#include <vector>
#include "Ball.hpp"
#include "Wall.hpp"

class Arena {
private:
  std::vector<Ball *> balls_;
  std::vector<Wall *> walls_;
  const glm::vec3 g = glm::vec3(0, -9.8, 0);
  const float mu = 0.2;
public:
  //everything in the universe is destined
  void deduce(const float t);
  void attach(Ball *ball);
  void attach(Wall *wall);
};
