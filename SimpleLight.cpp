#include "SimpleLight.hpp"

glm::vec4 SimpleLight::getPosition() const {
  return position;
}
glm::vec3 SimpleLight::getIntensities() const {
  return intensities;
}
float SimpleLight::getAttenuation() const {
  return attenuation;
}
float SimpleLight::getAmbientCoefficient() const {
  return ambientCoefficient;
}
float SimpleLight::getConeAngle() const {
  return coneAngle;
}
glm::vec3 SimpleLight::getConeDirection() const {
  return coneDirection;
}
