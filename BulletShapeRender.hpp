#pragma once

#include "Shape.hpp"
#include "Renderable.hpp"
#include "utils.hpp"
#include <LinearMath/btMotionState.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Log.hpp"

#include "BulletShape.hpp"

class BulletShapeRender : public Renderable {
private:
  const BulletShape *shape_;
  const btMotionState *const motionState_;
  const Material material_;
public:
  BulletShapeRender(const BulletShape *const shape, const btMotionState *const motionState, const Material &material)
    :shape_(shape), motionState_(motionState), material_(material) {}

  const BulletShape *getShape() {
    return shape_;
  }
  
  void render(ModelSetter ms, MaterialSetter ts) const {
    btTransform tf;
    motionState_->getWorldTransform(tf);

    ts(material_);
    shape_->draw([&tf, &ms](const glm::vec3 &sca) -> void {
        glm::mat4 translate = glm::translate(glm::mat4(), convert(tf.getOrigin()));
        btQuaternion quaternion = tf.getRotation();
        glm::mat4 rotate = glm::rotate(translate, quaternion.getAngle(), convert(quaternion.getAxis()));
        ms(glm::scale(rotate, sca));
      });
  }
};
