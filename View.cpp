#include "View.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Window.hpp>
#include <glm/gtc/constants.hpp>

View::View(const glm::vec3 &eye, const glm::vec2 &angle)
  :eye_(eye), angle_(angle) {
  turn(glm::vec2(0, 0));
}


void View::turn(const glm::vec2 &d) {
  angle_ += d;
  direction_ = glm::vec3(
                         cos(angle_.y) * sin(angle_.x),
                         sin(angle_.y),
                         cos(angle_.y) * cos(angle_.x)
                         );
  right_ = glm::vec3(
                     sin(angle_.x - glm::pi<float>() / 2),
                     0,
                     cos(angle_.x - glm::pi<float>() / 2)
                     );

  up_ = glm::cross(right_, direction_);
}

void View::up(const float d) {
  eye_ += up_ * d;
}

void View::right(const float d) {
  eye_ += right_ * d;
}

glm::mat4 View::matrix() const {
  return glm::lookAt(eye_, eye_ + direction_, up_);
}
