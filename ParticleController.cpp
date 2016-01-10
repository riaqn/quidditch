#include "ParticleController.hpp"
#include <glm/glm.hpp>


void ParticleController::init(WorldProxy &world) {
  world_ = &world;
  for (auto rb : group_) {
    world.add(rb, particleFilter, ~particleFilter);
  }
}
  
bool ParticleController::control(const float elapsed) {
  float survive = glm::pow(0.5, elapsed / halflife_);

  auto it = group_.begin();
  
  while (it != group_.end()) {
    if (random<float>(0, 1) > survive) {
      world_->remove(*it);
      delete *it;
      *it = group_.back();
      group_.resize(group_.size() - 1);
    } else
      ++it;
  }
  if (it == group_.begin())
    return true;
  else
    return false;
}
