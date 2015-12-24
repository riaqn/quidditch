#pragma once
#include <glm/glm.hpp>

class Light {
public:
  virtual glm::vec4 getPosition() const = 0;
  virtual glm::vec3 getIntensities() const = 0;
  virtual float getAttenuation() const = 0;
  virtual float getAmbientCoefficient() const = 0;
  virtual float getConeAngle() const = 0;
  virtual glm::vec3 getConeDirection() const = 0;
};
