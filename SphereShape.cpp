#include "SphereShape.hpp"

void SphereShape::draw(ScaleSetter ss) const {
  ss(glm::vec3(shape_->getRadius()));
  if (sphere_ == NULL)
    sphere_ = new Sphere();
  sphere_->draw();
}

const Sphere *SphereShape::sphere_ = NULL;
