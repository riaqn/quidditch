#include <BulletSoftBody/btSoftBody.h>
#include "PrimitiveShape.hpp"
#include "BulletShape.hpp"
#include "utils.hpp"

class SoftBodyShape : public PrimitiveShape, public BulletShape {
  const btSoftBody &sb_;
public:
  SoftBodyShape(const btSoftBody &sb,
                const std::vector<UV> &uv)
    :sb_(sb) {
    load(uv);
  }

  virtual void render(Render::ModelSetter ms) const;
};
