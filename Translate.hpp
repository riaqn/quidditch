#include <glm/glm.hpp>
#include "Renderable.hpp"
class Translate : public Renderable {
private:
  const Renderable &r_;
  const glm::vec3 v_;
public:
  Translate(const Renderable &r, const glm::vec3 v);
  virtual void render(ModelSetter ms, MaterialSetter ts) const;
};
