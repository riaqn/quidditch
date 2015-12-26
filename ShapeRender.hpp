#pragma once

#include "Shape.hpp"
#include "Renderable.hpp"
#include "utils.hpp"
#include <LinearMath/btMotionState.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Log.hpp"

class ShapeRender : public Renderable {
private:
  const Shape *shape_;
  const btMotionState *const motionState_;
  const Material material_;
public:
  ShapeRender(const Shape *const shape, const btMotionState *const motionState, const Material &material)
    :shape_(shape), motionState_(motionState), material_(material) {}
  
  void render(ModelSetter ms, MaterialSetter ts) const {
    btTransform tf;
    motionState_->getWorldTransform(tf);

    glm::mat4 translate = glm::translate(glm::mat4(), convert(tf.getOrigin()));
    ms(translate);
    ts(material_);
    shape_->draw();
  }
};
