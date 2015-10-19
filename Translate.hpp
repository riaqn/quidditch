#include "Renderable.hpp"
#include <glm/glm.hpp>

class Translate : public Renderable {
private:
  glm::vec3 v_;
  Renderable *r_;
public:
  Translate(const glm::vec3 &&v, Renderable *r);
  virtual void render(const GLuint WVP, const glm::mat4 &mat);
};
