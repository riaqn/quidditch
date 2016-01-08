#pragma once

#include <functional>
#include <glm/glm.hpp>

/*
  actually a particle system containing lots of particles
 */
class Particle {
public:
  struct Material {
    float shininess;
    glm::vec3 specularColor;
    float brightness;
  };
  typedef std::function<void (const Material &)> MaterialSetter;
  virtual void render(MaterialSetter ts) const = 0;
};
