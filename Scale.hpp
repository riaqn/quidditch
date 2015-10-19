#include "Renderable.hpp"

class Scale : public Renderable {
private:
  const Renderable &r_;
  glm::vec3 v_;
public:
  Scale(const Renderable &r, const glm::vec3 &v);
  Scale(const Renderable &&r, const glm::vec3 &v);
  virtual void render(const GLuint WVP, const glm::mat4 &mat) const;
};
