#include "BallWrapper.hpp"

#include "Sphere.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "utils.hpp"
#include "Log.hpp"

BallWrapper::BallWrapper(const float r, const btMotionState *motionState, const Sphere &sphere, const Texture &texture)
  :r_(r), motionState_(motionState), sphere_(sphere), texture_(texture)
{ }

void BallWrapper::render(ModelSetter ms, MaterialSetter ts) const {
  btTransform tf;
  motionState_->getWorldTransform(tf);
  
  glm::mat4 translate = glm::translate(glm::mat4(), convert(tf.getOrigin()));
  debug << glm::to_string(convert(tf.getOrigin())) << "\n";
  glm::mat4 scale = glm::scale(translate, glm::vec3(r_));
  ms(scale);

  ts(Material{texture_, 40, glm::vec3{1, 1, 1}});

  sphere_.draw();
}
