#pragma once

#include <BulletCollision/CollisionShapes/btTriangleMeshShape.h>

#include "BulletShape.hpp"
#include "PrimitiveShape.hpp"
class TriangleMeshShape : public PrimitiveShape, public BulletShape {
public:
  TriangleMeshShape(const btTriangleMeshShape *const shape, const int i);
};
