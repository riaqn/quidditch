#include "Renderable.hpp"
#include "Ball.hpp"
#include "Sphere.hpp"
#include "Texture.hpp"
#include <LinearMath/btMotionState.h>

class BallWrapper : public Renderable {
private:
  const float r_;
  const btMotionState *motionState_;
  const Sphere &sphere_;
  const Texture &texture_;
public:
  BallWrapper(const float r, const btMotionState *motionState, const Sphere &sphere, const Texture &texture);
  virtual void render(ModelSetter ms, MaterialSetter ts) const;
};
