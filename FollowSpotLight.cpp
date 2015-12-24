#include "FollowSpotLight.hpp"

FollowSpotLight::FollowSpotLight(const Ball &ball, const glm::vec3 &position, const glm::vec3 &intensities, const float attenuation, const float coneAngle)
  :ball_(ball), position_(glm::vec4(position, 1)), intensities_(intensities), attenuation_(attenuation), coneAngle_(coneAngle) {}

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
  return ball_.x - glm::vec3(position_);
}
