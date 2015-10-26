#include <vector>
#include <functional>
#include "Ball.hpp"
#include "Wall.hpp"

class Arena {
private:
  std::vector<Ball *> balls_;
  std::vector<Wall *> walls_;
  const glm::vec3 g = glm::vec3(0, -9.8, 0);
  const float mu = 0.01;

  bool onGround(const Ball *ball) const ;

  std::function<void(const Wall *, const Ball *)> cb0_;
  std::function<void(const Ball *, const Ball *)> cb1_;
public:
  Arena(std::function<void(const Wall *, const Ball *)> cb0,
        std::function<void(const Ball *, const Ball *)> cb1);
  unsigned score = 0;
  //everything in the universe is destined
  void deduce(const float t);
  void attach(Ball *ball);
  void attach(Wall *wall);
};
