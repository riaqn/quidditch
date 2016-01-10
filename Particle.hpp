#pragma once

#include <functional>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

/*
  actually a particle system containing lots of particles
 */
class Particle {
  GLuint vert_;
  GLuint index_;
  GLuint vertOffset_;
  GLuint vertNormal_;
  GLuint vertColor_;

  const size_t n_;
public:
  struct Material {
    float shininess;
    glm::vec3 specularColor;
    float brightness;
  };
public:
  Particle(const size_t n);
  ~Particle() {
    glDeleteBuffers(1, &vert_);
    glDeleteBuffers(1, &vertNormal_);
    glDeleteBuffers(1, &vertOffset_);
    glDeleteBuffers(1, &vertColor_);
  }
  
  typedef std::function<void (const Material &)> MaterialSetter;
  virtual void render(MaterialSetter ts) const = 0;
  void renderHelper(const std::vector<glm::vec4> &vertOffset,
                    const std::vector<glm::vec4> &vertColor) const;
};
