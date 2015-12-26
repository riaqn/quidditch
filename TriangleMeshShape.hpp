#include <BulletCollision/CollisionShapes/btTriangleMeshShape.h>

#include "Shape.hpp"
class TriangleMeshShape : public Shape {
public:
  TriangleMeshShape(const btTriangleMeshShape *const shape, const int i);
};
