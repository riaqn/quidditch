#pragma once
#include "Renderable.hpp"
#include "Ball.hpp"
#include "Sphere.hpp"
#include "Texture.hpp"
#include <LinearMath/btMotionState.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>

class SphereRender : public Renderable {
private:
  const btSphereShape *shape_;
  const btMotionState *motionState_;
  const Material material_;
  const static Sphere *sphere_;
public:
  SphereRender(const btSphereShape *shape, const btMotionState *motionState, const Material &material);
  virtual void render(ModelSetter ms, MaterialSetter ts) const;
};

