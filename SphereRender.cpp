#include "SphereRender.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "utils.hpp"
#include "Log.hpp"

SphereRender::SphereRender(const btSphereShape *shape, const btMotionState *motionState, const Material &material)
  :shape_(shape), motionState_(motionState),  material_(material) { }

void SphereRender::render(ModelSetter ms, MaterialSetter ts) const {
  btTransform tf;
  motionState_->getWorldTransform(tf);
  
  glm::mat4 translate = glm::translate(glm::mat4(), convert(tf.getOrigin()));
  glm::mat4 scale = glm::scale(translate, glm::vec3(shape_->getRadius()));
  ms(scale);

  ts(material_);

  if (sphere_ == NULL)
    sphere_ = new Sphere();
  sphere_->draw();
}

const Sphere *SphereRender::sphere_ = NULL;
