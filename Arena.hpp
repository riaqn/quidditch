#include <vector>
#include "Ball.hpp"

class Arena {
private:
  std::vector<Ball *> balls_;
  const float g = 9.8;
  const float mu = 0.2;
public:
  //everything in the universe is destined
  void deduce(const float t);
  void attach(Ball *ball);
};
