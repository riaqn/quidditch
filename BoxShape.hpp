#pragma once

#include "BulletShape.hpp"
#include "Cube.hpp"
#include <BulletCollision/CollisionShapes/btBoxShape.h>

class BoxShape : public BulletShape {
private:
  const Cube cube_;
  const btBoxShape &shape_;
public:
  BoxShape(const btBoxShape &shape)
    :cube_(), shape_(shape) {}
  virtual void render(Render::ModelSetter ms) const ;
};
