#include <LinearMath/btMotionState.h>
#include "Light.hpp"
#include "utils.hpp"

class MovingLight : public Light {
  const btMotionState *motionState_;
  const Light &light_;
public:
  MovingLight(const btMotionState *const motionState, const Light &light)
    :motionState_(motionState), light_(light) {}
  
  virtual Spec operator() () const {
    Spec spec = light_();
    btTransform tf;
    motionState_->getWorldTransform(tf);
    spec.position = glm::vec4(convert(tf.getOrigin()), 1);
    return spec;
  }
};
