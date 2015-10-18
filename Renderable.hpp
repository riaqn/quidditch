#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

class Renderable {
public:
  virtual void render(const GLuint WVP, const glm::mat4 &mat) = 0;
};

#endif
