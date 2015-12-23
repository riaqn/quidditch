#pragma  once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <functional>

class Renderable {
public:
  typedef std::function<void (const glm::mat4 &)> ModelSetter;
  typedef std::function<void (const GLenum)> TextureSetter;
  virtual void render(ModelSetter ms, TextureSetter ts) const = 0;
};

