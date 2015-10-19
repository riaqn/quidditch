#include "Renderable.hpp"
#include <glm/glm.hpp>

class Translate : public Renderable {
private:
  const glm::vec3 &v_;
  const Renderable &r_;
public:
  Translate(const Renderable &r, const glm::vec3 &v);
  virtual void render(const GLuint WVP, const glm::mat4 &mat) const ;
};
