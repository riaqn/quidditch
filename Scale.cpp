#include "Scale.hpp"
#include <glm/gtc/matrix_transform.hpp>

Scale::Scale(Renderable *const r, const glm::vec3 &v)
  :r_(r), v_(v) {}

void Scale::render(const GLuint WVP, const glm::mat4 &mat) {
  r_->render(WVP, mat * glm::scale(glm::mat4(), v_));
}

