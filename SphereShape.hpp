#pragma once
#include "Sphere.hpp"
#include "BulletShape.hpp"

#include <BulletCollision/CollisionShapes/btSphereShape.h>

class SphereShape : public BulletShape {
private:
  const btSphereShape *shape_;
  const static Sphere *sphere_;
public:
  SphereShape(const btSphereShape *const shape)
    :shape_(shape) {}
  virtual void render(Render::ModelSetter ss) const ;
};

