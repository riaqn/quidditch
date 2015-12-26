#pragma once
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include "BulletShape.hpp"
#include "Box.hpp"

class BoxShape : public BulletShape {
  const btBoxShape *shape_;
  const static Box *box_;
public:
  BoxShape(const btBoxShape *const shape)
    :shape_(shape) {}
  virtual void draw(ScaleSetter ss) const;
};
