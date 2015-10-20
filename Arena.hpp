#include <vector>
#include "Ball.hpp"
#include "Wall.hpp"

class Arena {
private:
  std::vector<Ball *> balls_;
  std::vector<Wall *> walls_;
  const float g = 9.8;
  const float mu = 0.2;
public:
  //everything in the universe is destined
  void deduce(const float t);
  void attach(Ball *ball);
  void attach(Wall *wall);
};
