#include "BallWrapper.hpp"

#include "Sphere.hpp"
#include <glm/gtc/matrix_transform.hpp>

BallWrapper::BallWrapper(const Ball &ball, const Sphere &sphere, const Texture &texture)
  :ball_(ball), sphere_(sphere), texture_(texture)
{ }

void BallWrapper::render(ModelSetter ms, MaterialSetter ts) const {
  const Ball &ball = ball_;
  glm::mat4 translate = glm::translate(glm::mat4(), ball.x);
  glm::mat4 scale = glm::scale(translate, glm::vec3(ball.r));
  ms(scale);
  
  ts(Material{texture_, 40, glm::vec3{1, 1, 1}});
  sphere_.draw();
}
