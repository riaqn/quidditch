#include <glm/glm.hpp>
#include "Render.hpp"
class Translate : public Render {
private:
  const Render &r_;
  const glm::vec3 v_;
public:
  Translate(const Render &r, const glm::vec3 v);
  virtual void render(ModelSetter ms, MaterialSetter ts) const;
};
