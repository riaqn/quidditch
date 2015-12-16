#include "Scale.hpp"
#include <glm/gtc/matrix_transform.hpp>

Scale::Scale(const Renderable &r, const glm::vec3 v)
  :r_(r), v_(v) {
}
void Scale::render(const GLuint WVP, const glm::mat4 &mat) const {
  r_.render(WVP, glm::scale(mat, v_));
}
