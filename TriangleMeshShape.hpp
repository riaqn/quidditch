#pragma once

#include <BulletCollision/CollisionShapes/btTriangleMeshShape.h>

#include "BulletShape.hpp"
#include "Shape.hpp"
class TriangleMeshShape : public BulletShape {
  Shape shape_;
public:
  TriangleMeshShape(const btTriangleMeshShape *const shape, const int i);
  virtual void draw(ScaleSetter ss) const;
};
