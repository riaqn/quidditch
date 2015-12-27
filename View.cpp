#include "View.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Window.hpp>
#include <glm/gtc/constants.hpp>

View::View(const glm::vec3 &eye, const glm::vec2 &angle)
  :eye(eye), angle(angle) {
  turn(glm::vec2(0, 0));
}


void View::turn(const glm::vec2 &d) {
  angle += d;
  direction = glm::vec3(
                         cos(angle.y) * sin(angle.x),
                         sin(angle.y),
                         cos(angle.y) * cos(angle.x)
                         );
  right = glm::vec3(
                     sin(angle.x - glm::pi<float>() / 2),
                     0,
                     cos(angle.x - glm::pi<float>() / 2)
                     );

  up = glm::cross(right, direction);
}

void View::moveUp(const float d) {
  eye += up * d;
}

void View::moveRight(const float d) {
  eye += right * d;
}

glm::mat4 View::matrix() const {
  return glm::lookAt(eye, eye + direction, up);
}

void View::zoom(const float d) {
  eye += d * direction;
}
