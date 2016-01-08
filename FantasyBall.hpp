#include "Ball.hpp"
class FantasyBall : public Ball {
private:
  float duration_;
public:
  FantasyBall(Ball &&ball, const float duration)
    :Ball(std::move(ball)), duration_(duration) {}

  float getDuration() {
    return duration_;
  }
};
