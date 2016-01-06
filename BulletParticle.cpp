#include "BulletParticle.hpp"

#include <vector>
#include <glm/glm.hpp>

BulletParticle::BulletParticle(const std::vector<btRigidBody *> &particles, const Material &material)
  :particles_(particles),
   n_(particles.size()),
   material_(material) {
  float phi = 1 / sqrt(2);

  std::vector<glm::vec3> v({
      glm::vec3(0, 1, phi), //3
        glm::vec3(-1, 0, -phi), //0
        glm::vec3(0, -1, phi), //4
        glm::vec3(1, 0, -phi), //1
        glm::vec3(0, 1, phi), //2
        glm::vec3(-1, 0, -phi) //5
        });

  glGenBuffers(1, &vert_);
  glBindBuffer(GL_ARRAY_BUFFER, vert_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), &v[0].x, GL_STATIC_DRAW);
  
  glGenBuffers(1, &vertNormal_);
  glBindBuffer(GL_ARRAY_BUFFER, vertNormal_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), &v[0].x, GL_STATIC_DRAW);

  glGenBuffers(1, &vertColor_);
  glBindBuffer(GL_ARRAY_BUFFER, vertColor_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * n_, NULL, GL_STREAM_DRAW);

  glGenBuffers(1, &vertOffset_);
  glBindBuffer(GL_ARRAY_BUFFER, vertOffset_);
  glBufferData(vertOffset_, sizeof(btVector4) * n_, NULL, GL_STREAM_DRAW);
}

void BulletParticle::render(MaterialSetter ts) const {
  ts(material_);

  std::vector<btVector4> vertOffset;
  std::vector<glm::vec4> vertColor;

  if (particles_.size() != n_)
    throw std::runtime_error("particles.size() changed");

  for (auto it = particles_.begin();
       it != particles_.end();
       ++it) {
    btRigidBody *rb = *it;
    if (rb != NULL) {
      btTransform tf;
      rb->getMotionState()->getWorldTransform(tf);
      btVector3 pos = tf.getOrigin();
      vertOffset.push_back(btVector4(pos.x(), pos.y(), pos.z(), 0.0001f));
      vertColor.push_back(colors_[it - particles_.begin()]);
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, vertOffset_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(btVector3) * n_, NULL, GL_STREAM_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertOffset.size() * sizeof(vertOffset[0]), &vertOffset[0]);

  //begin color
  glBindBuffer(GL_ARRAY_BUFFER, vertColor_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * n_, NULL, GL_STREAM_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertColor.size() * sizeof(vertColor[0]), &vertColor[0].x);


  //start rendering!!
  glBindBuffer(GL_ARRAY_BUFFER, vert_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, vertOffset_);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, vertNormal_);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, vertColor_);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, NULL);

  glVertexAttribDivisor(0, 0);
  glVertexAttribDivisor(1, 1);
  glVertexAttribDivisor(2, 0);
  glVertexAttribDivisor(3, 1);

  glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6, vertOffset.size());

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
