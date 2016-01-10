#include "SmokeController.hpp"
#include "Log.hpp"

bool SmokeController::control(const float elapsed) {
  btVector3 pmin, pmax;
  rb_.getAabb(pmin, pmax);
  for (auto i = 0; i < elapsed * rate_; ++i) {
    glm::vec4 offset(convert<glm::vec3>(random(pmin, pmax)), 0.002f);
    if (off_ == vertOffset_.size())
      vertOffset_.push_back(offset);
    else 
      vertOffset_[off_] = offset;
    ++off_;
    if (off_ == num_)
      off_ = 0;
  }

  for (auto &offset : vertOffset_) {
    auto offset0 = glm::vec3(offset) / 2.0f;
    offset.x += noise_.noise(glm::vec3(0, offset0.y, offset.z)) * elapsed;
    offset.y += (noise_.noise(glm::vec3(offset0.x, 0, offset0.z)) + 0.1f) * elapsed;
    offset.z += noise_.noise(glm::vec3(offset0.x, offset0.y, 0)) * elapsed;
    //debug << "offset = " << offset << '\n';
    /*if (isnanf(offset.x) || isnanf(offset.y) || isnanf(offset.z))
      throw std::runtime_error("NaN detected");*/
    
  }

  return false;
}
