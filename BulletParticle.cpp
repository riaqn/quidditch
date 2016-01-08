#include "BulletParticle.hpp"

#include <vector>
#include <glm/glm.hpp>
#include "Log.hpp"

BulletParticle::BulletParticle(const GroupController::Group  &particles,
                               const std::vector<glm::vec4> &colors,
                               const Material &material)
  :particles_(particles),
   colors_(colors),
   n_(particles.size()),
   material_(material) {
  if (colors.size() != n_)
    throw std::runtime_error("particles and colors number not match");
  float phi = 1 / sqrt(2);

  std::vector<glm::vec3> v({
      glm::vec3(0, 1, phi),
        glm::vec3(0, -1, phi),
        glm::vec3(1, 0, -phi),
        glm::vec3(-1, 0, -phi),
        glm::vec3(0, 1, phi),
        glm::vec3(0, -1, phi)
        });

  glGenBuffers(1, &vert_);
  glBindBuffer(GL_ARRAY_BUFFER, vert_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), &v[0].x, GL_STATIC_DRAW);
  
  glGenBuffers(1, &vertNormal_);
  glBindBuffer(GL_ARRAY_BUFFER, vertNormal_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), &v[0].x, GL_STATIC_DRAW);

  glGenBuffers(1, &vertOffset_);
  glBindBuffer(GL_ARRAY_BUFFER, vertOffset_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * n_, NULL, GL_STREAM_DRAW);

  glGenBuffers(1, &vertColor_);
  glBindBuffer(GL_ARRAY_BUFFER, vertColor_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * n_, NULL, GL_STREAM_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

BulletParticle::~BulletParticle() {
  glDeleteBuffers(1, &vert_);
  glDeleteBuffers(1, &vertNormal_);
  glDeleteBuffers(1, &vertOffset_);
  glDeleteBuffers(1, &vertColor_);
}

void BulletParticle::render(MaterialSetter ts) const {
  ts(material_);

  std::vector<glm::vec4> vertOffset;
  std::vector<glm::vec4> vertColor;

  if (particles_.size() > n_ || colors_.size() > n_)
    throw std::runtime_error("particles.size() increased");

  size_t i = 0;
  for (auto it = particles_.begin();
       it != particles_.end();
       ++it, ++i) {
    btRigidBody *rb = *it;
    if (rb != NULL) {
      btTransform tf;
      rb->getMotionState()->getWorldTransform(tf);
      btVector3 pos = tf.getOrigin();
      vertOffset.push_back(glm::vec4(pos.x(), pos.y(), pos.z(), 0.02f));
      vertColor.push_back(colors_[i]);
    }
  }


  glBindBuffer(GL_ARRAY_BUFFER, vertOffset_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * n_, NULL, GL_STREAM_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertOffset.size() * sizeof(glm::vec4), &vertOffset[0]);

  //begin color
  glBindBuffer(GL_ARRAY_BUFFER, vertColor_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * n_, NULL, GL_STREAM_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertColor.size() * sizeof(glm::vec4), &vertColor[0]);


  //start rendering!!
  glBindBuffer(GL_ARRAY_BUFFER, vert_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, vertNormal_);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  
  glBindBuffer(GL_ARRAY_BUFFER, vertOffset_);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, vertColor_);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, NULL);

  glVertexAttribDivisor(0, 0);
  glVertexAttribDivisor(1, 0);
  glVertexAttribDivisor(2, 1);
  glVertexAttribDivisor(3, 1);

  glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6, vertOffset.size());

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
