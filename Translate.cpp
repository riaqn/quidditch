#include "Translate.hpp"
#include <glm/gtc/matrix_transform.hpp>

Translate::Translate(const glm::vec3 &&v, Renderable *r)
  :v_(v), r_(r) {
}

void Translate::render(const GLuint WVP, const glm::mat4 &mat) {
  r_->render(WVP, mat * glm::translate(glm::mat4(), v_));
}
