#include "Light.hpp"

//I 'm not a Java programmer
struct SimpleLight : public Light {
  glm::vec4 position;
  glm::vec3 intensities;
  float attenuation;
  float ambientCoefficient;
  float coneAngle;
  glm::vec3 coneDirection;
  
  virtual glm::vec4 getPosition() const;
  virtual glm::vec3 getIntensities() const;
  virtual float getAttenuation() const;
  virtual float getAmbientCoefficient() const;
  virtual float getConeAngle() const;
  virtual glm::vec3 getConeDirection() const;
};
