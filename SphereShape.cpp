#include "SphereShape.hpp"
#include <glm/gtc/matrix_transform.hpp>

void SphereShape::render(Render::ModelSetter ms) const {
  if (sphere_ == NULL)
    sphere_ = new Sphere();
  sphere_->render([this, ms](const glm::mat4 &mat) {
      ms(glm::scale(glm::mat4(), glm::vec3(this->shape_->getRadius())) * mat);
    });
}

const Sphere *SphereShape::sphere_ = NULL;
