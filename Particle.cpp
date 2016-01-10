#include "Particle.hpp"

Particle::Particle(const size_t n)
  :n_(n) {
  float phi = 1 / sqrt(2);
  std::vector<glm::vec3> v({
      glm::vec3(0, 1, phi), //0
        glm::vec3(0, -1, phi), //1
        glm::vec3(1, 0, -phi), //2
        glm::vec3(-1, 0, -phi), //3
        });

  glGenBuffers(1, &vert_);
  glBindBuffer(GL_ARRAY_BUFFER, vert_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), &v[0], GL_STATIC_DRAW);

  glm::uvec3 i[] = {
    glm::vec3(0, 1, 2),
    glm::vec3(3, 0, 2),
    glm::vec3(3, 2, 1),
    glm::vec3(3, 1, 0)
  };

  glGenBuffers(1, &index_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i), i, GL_STATIC_DRAW);

  glGenBuffers(1, &vertNormal_);
  glBindBuffer(GL_ARRAY_BUFFER, vertNormal_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), &v[0], GL_STATIC_DRAW);

  glGenBuffers(1, &vertOffset_);
  glBindBuffer(GL_ARRAY_BUFFER, vertOffset_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * n_, NULL, GL_STREAM_DRAW);

  glGenBuffers(1, &vertColor_);
  glBindBuffer(GL_ARRAY_BUFFER, vertColor_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * n_, NULL, GL_STREAM_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Particle::renderHelper(const std::vector<glm::vec4> &vertOffset,
                            const std::vector<glm::vec4> &vertColor) const {
  if (vertOffset.size() > n_ || vertColor.size() > n_)
    throw std::runtime_error("particles.size() increased");

  glBindBuffer(GL_ARRAY_BUFFER, vertOffset_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * n_, NULL, GL_STREAM_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertOffset.size() * sizeof(glm::vec4), &vertOffset[0]);

  //begin color
  glBindBuffer(GL_ARRAY_BUFFER, vertColor_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * n_, NULL, GL_STREAM_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertColor.size() * sizeof(glm::vec4), &vertColor[0]);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

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

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_);
  glDrawElementsInstanced(GL_TRIANGLES, 12, GL_UNSIGNED_INT, NULL, vertOffset.size());
  glVertexAttribDivisor(0, 0);
  glVertexAttribDivisor(1, 0);
  glVertexAttribDivisor(2, 0);
  glVertexAttribDivisor(3, 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
