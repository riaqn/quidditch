#include <glm/glm.hpp>
#include "Renderable.hpp"
class Scale : public Renderable {
private:
  const Renderable &r_;
  const glm::vec3 v_;
public:
  Scale(const Renderable &r, const glm::vec3 v);
  virtual void render(ModelSetter setter, MaterialSetter ts) const;
};
