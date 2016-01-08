#pragma once
#include <glm/glm.hpp>
#include <functional>
class Light {
public:
  struct Spec {
    glm::vec4 position;
    glm::vec3 intensities;
    float attenuation;
    float ambientCoefficient;
    float coneAngle;
    glm::vec3 coneDirection;
  };
  virtual Spec operator() () const = 0;
};
