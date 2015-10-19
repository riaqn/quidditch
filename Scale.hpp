#include "Renderable.hpp"

class Scale : public Renderable {
private:
  Renderable *const r_;
  glm::vec3 v_;
public:
  Scale(Renderable *const r, const glm::vec3 &v);
  virtual void render(const GLuint WVP, const glm::mat4 &mat);
};
