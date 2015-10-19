#include "Translate.hpp"
#include <glm/gtc/matrix_transform.hpp>

Translate::Translate(const Renderable &r, const glm::vec3 &v)
  :v_(v), r_(r) {
}

void Translate::render(const GLuint WVP, const glm::mat4 &mat) const {
  r_.render(WVP, glm::translate(mat, v_));
}
