#include "BulletParticle.hpp"

#include <vector>
#include <glm/glm.hpp>
#include "Log.hpp"

BulletParticle::BulletParticle(const GroupController::Group  &particles,
                               const std::vector<glm::vec4> &colors,
                               const Material &material)
  :Particle(particles.size()),
   particles_(particles),
   colors_(colors),
   material_(material) {
  if (colors.size() != particles.size())
    throw std::runtime_error("particles and colors number not match");
}

void BulletParticle::render(MaterialSetter ts) const {
  std::vector<glm::vec4> vertOffset;
  std::vector<glm::vec4> vertColor;

  size_t i = 0;
  for (auto it = particles_.begin();
       it != particles_.end();
       ++it, ++i) {
    btRigidBody *rb = *it;
    if (rb != NULL) {
      btTransform tf;
      rb->getMotionState()->getWorldTransform(tf);
      btVector3 pos = tf.getOrigin();
      vertOffset.push_back(glm::vec4(pos.x(), pos.y(), pos.z(), 0.005f));
      vertColor.push_back(colors_[i]);
    }
  }

  ts(material_);
  renderHelper(vertOffset, vertColor);
}
