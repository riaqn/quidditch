#include <LinearMath/btMotionState.h>
#include "Light.hpp"
#include "Ball.hpp"
#include "utils.hpp"

class FollowSpotLight : public Light {
  const btMotionState *motionState_;
  const Light &light_;
public:
  FollowSpotLight(const btMotionState *const motionState, const Light &light)
    :motionState_(motionState), light_(light) {}
  
  Spec operator() () const {
    Spec spec = light_();
    btTransform tf;
    motionState_->getWorldTransform(tf);
    spec.coneDirection = convert<glm::vec3>(tf.getOrigin()) - glm::vec3(spec.position);
    return spec;
  }
};

