#pragma once

#include "Shape.hpp"
#include "Render.hpp"
#include "utils.hpp"
#include <LinearMath/btMotionState.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Log.hpp"


class BulletShapeRender : public Render {
private:
  const Shape *shape_;
  const btMotionState *const motionState_;
  const Material material_;
public:
  BulletShapeRender(const Shape *const shape, const btMotionState *const motionState, const Material &material)
    :shape_(shape), motionState_(motionState), material_(material) {}

  const Shape *getShape() {
    return shape_;
  }
  
  void render(ModelSetter ms, MaterialSetter ts) const {
    btTransform tf;
    motionState_->getWorldTransform(tf);

    ts(material_);
    shape_->render([&tf, &ms](const glm::mat4 &mat) -> void {
        glm::mat4 translate = glm::translate(glm::mat4(), convert<glm::vec3>(tf.getOrigin()));
        btQuaternion quaternion = tf.getRotation();
        glm::mat4 rotate = glm::rotate(translate, quaternion.getAngle(), convert<glm::vec3>(quaternion.getAxis()));
        ms(rotate * mat);
      });
  }
};
