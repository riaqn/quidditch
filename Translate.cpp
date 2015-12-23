#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Translate.hpp"

Translate::Translate(const Renderable &r, const glm::vec3 v)
  :r_(r), v_(v) {
}

void Translate::render(ModelSetter ms, MaterialSetter ts) const {
  const glm::vec3 &v = v_;
  r_.render([&ms, &v](const glm::mat4 &mat) -> void {
      ms(glm::translate(mat, v));      
    }, ts);
}
