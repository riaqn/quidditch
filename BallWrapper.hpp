#include "Renderable.hpp"
#include "Ball.hpp"
#include "Sphere.hpp"
#include "Texture.hpp"

class BallWrapper : public Renderable {
private:
  const Ball &ball_;
  const Sphere &sphere_;
  const Texture &texture_;
public:
  BallWrapper(const Ball &ball, const Sphere &sphere, const Texture &texture);
  virtual void render(ModelSetter ms, TextureSetter ts) const;
};
