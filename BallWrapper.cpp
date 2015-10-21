#include "BallWrapper.hpp"

#include "Sphere.hpp"
#include <glm/gtc/matrix_transform.hpp>

BallWrapper::BallWrapper(const Ball &ball, const Sphere &sphere, const Texture &texture)
  :ball_(ball), sphere_(sphere), texture_(texture)
{ }

void BallWrapper::render(const GLuint WVP, const glm::mat4 &mat) const {
  glm::mat4 translate = glm::translate(mat, ball_.x);
  glm::mat4 scale = glm::scale(translate, glm::vec3(ball_.r));

  texture_.bind(GL_TEXTURE0);
  sphere_.render(WVP, scale);
}
