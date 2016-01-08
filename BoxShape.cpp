#include "BoxShape.hpp"
#include "utils.hpp"
#include <glm/gtc/matrix_transform.hpp>

void BoxShape::render(Render::ModelSetter ms) const {
  cube_.render([this, ms](const glm::mat4 &mat) {
      ms(glm::scale(glm::mat4(), convert(this->shape_.getHalfExtentsWithMargin())) * mat);
    });
}
