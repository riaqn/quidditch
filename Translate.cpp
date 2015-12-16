#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Translate.hpp"

Translate::Translate(const Renderable &r, const glm::vec3 v)
  :r_(r), v_(v) {
}

void Translate::render(const GLuint WVP, const glm::mat4 &mat) const {
  r_.render(WVP, glm::translate(mat, v_));
}
