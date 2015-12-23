#include "Scale.hpp"
#include <glm/gtc/matrix_transform.hpp>

Scale::Scale(const Renderable &r, const glm::vec3 v)
  :r_(r), v_(v) {
}

void Scale::render(ModelSetter ms, MaterialSetter ts) const {
  const glm::vec3 &v = v_;
  r_.render([&ms, &v](const glm::mat4 &mat) -> void {
      ms(glm::scale(mat, v));
    }, ts);
}
