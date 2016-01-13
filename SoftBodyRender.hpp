#include "Render.hpp"
#include "Shape.hpp"

class SoftBodyRender : public Render {
  const Shape *shape_;
  const Material &material_;
public:
  SoftBodyRender(const Shape *const shape,
                 const Material &material)
    :shape_(shape), material_(material) {}

  void render(ModelSetter ms, MaterialSetter ts) const {
    ts(material_);
    shape_->render(ms);
  }
};
