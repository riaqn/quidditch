#include "ParticleController.hpp"
#include <glm/glm.hpp>

void ParticleController::init(AddCallback cb) {
  for (auto rb : group_) {
    cb(rb, particleFilter, ~particleFilter);
  }
}
  
bool ParticleController::control(const float elapsed,
                                 RemoveCallback cb) {
  float survive = glm::pow(0.5, elapsed / halflife_);

  auto it = group_.begin();
  
  while (it != group_.end()) {
    if (dist_(eng_) > survive) {
      auto it0 = next(it);
      delete *it;
      group_.remove(*it);
      cb(*it);
      it = it0;
    } else
      ++it;
  }
  if (it == group_.begin())
    return true;
  else
    return false;
}

std::random_device ParticleController::dev_;
std::default_random_engine ParticleController::eng_(dev_());
std::uniform_real_distribution<float> ParticleController::dist_(0, 1);
