#include <glm/glm.hpp>

struct Light {
  glm::vec4 position;
  glm::vec3 intensities;
  float attenuation;
  float ambientCoefficient;
  float coneAngle;
  glm::vec3 coneDirection;
};
