#include <glm/glm.hpp>
#include "Render.hpp"
class Scale : public Render {
private:
  const Render &r_;
  const glm::vec3 v_;
public:
  Scale(const Render &r, const glm::vec3 v);
  virtual void render(ModelSetter setter, MaterialSetter ts) const;
};
