#include "FollowSpotLight.hpp"
#include "utils.hpp"

FollowSpotLight::FollowSpotLight(const btMotionState *const motionState, const glm::vec3 &position, const glm::vec3 &intensities, const float attenuation, const float coneAngle)
  :motionState_(motionState), position_(glm::vec4(position, 1)), intensities_(intensities), attenuation_(attenuation), coneAngle_(coneAngle) {}

glm::vec4 FollowSpotLight::getPosition() const {
  return position_;
}

glm::vec3 FollowSpotLight::getIntensities() const {
  return intensities_;
}

float FollowSpotLight::getAttenuation() const {
  return attenuation_;
}

float FollowSpotLight::getAmbientCoefficient() const {
  return 0;
}

float FollowSpotLight::getConeAngle() const {
  return coneAngle_;
}

glm::vec3 FollowSpotLight::getConeDirection() const {
  btTransform tf;
  motionState_->getWorldTransform(tf);
  return convert(tf.getOrigin()) - glm::vec3(position_);
}
