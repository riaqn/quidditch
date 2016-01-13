#include "BulletParticle.hpp"

#include <vector>
#include <glm/glm.hpp>
#include "Log.hpp"

void BulletParticle::render(MaterialSetter ts) const {
  std::vector<glm::vec4> vertOffset;

  size_t i = 0;
  for (auto it = particles_.begin();
       it != particles_.end();
       ++it, ++i) {
    auto rb = *it;
    btTransform tf;
    rb->getMotionState()->getWorldTransform(tf);
    btVector3 pos = tf.getOrigin();
    vertOffset.push_back(glm::vec4(pos.x(), pos.y(), pos.z(), size_));
    /*
    debug << vertOffset.back() << '\n';
    debug << vertColor_[i] << '\n';
    */
  }

  ts(material_);
  Particle::render(vertOffset, vertColor_);
}
