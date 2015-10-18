#include "ModelWrapper.hpp"
#include <glm/gtc/matrix_transform.hpp>

ModelWrapper::ModelWrapper(const glm::vec3 &&v, Renderable *r)
  :v_(v), r_(r) {
}


void ModelWrapper::render(const GLuint WVP, const glm::mat4 &mat) {
  glm::mat4 wvp = mat * glm::translate(glm::mat4(), v_);

  r_->render(WVP, wvp);
}
