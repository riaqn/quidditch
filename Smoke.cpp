#include "Smoke.hpp"
#include "Log.hpp"

bool Smoke::control(const float elapsed) {
  ts_ += elapsed;
  for (auto i = 0; i < elapsed * rate_; ++i) {
    glm::vec4 offset = cb_();
    if (off_ == vertOffset_.size()) {
      vertOffset_.push_back(offset);
      vertColor_.push_back(color_);
    } else {
      vertOffset_[off_] = offset;
      vertColor_[off_] = color_;
    }
    ++off_;
    if (off_ == num_)
      off_ = 0;
  }


  for (auto i = 0; i < vertOffset_.size(); ++i) {
    auto &offset = vertOffset_[i];
    auto offset0 = glm::vec3(offset) / 50.0f;
    offset.x += noise_.noise(glm::vec3(ts_ / 256, offset0.y, offset0.z)) * elapsed;
    offset.y += (noise_.noise(glm::vec3(offset0.x, ts_ / 256, offset0.z)) + 0.2) * elapsed;
    offset.z += noise_.noise(glm::vec3(offset0.x, offset0.y, ts_ / 256)) * elapsed;
    //debug << "offset = " << offset << '\n';
    /*if (isnanf(offset.x) || isnanf(offset.y) || isnanf(offset.z))
      throw std::runtime_error("NaN detected");*/

    vertColor_[i].w -= color_.w / (num_ / rate_) * elapsed;

    //vertColor_[i].w *= glm::pow(k_, elapsed / (num_ / rate_));

  }

  return false;
}
