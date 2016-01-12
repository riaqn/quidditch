#include "Particle.hpp"

Particle::Particle(const size_t n)
  :n_(n) {
  glm::vec3 vert[] = {
    glm::vec3(-1, -1, 0),
    glm::vec3(1, -1, 0),
    glm::vec3(-1, 1, 0),
    glm::vec3(1, 1, 0)
  };

  glGenBuffers(1, &vert_);
  glBindBuffer(GL_ARRAY_BUFFER, vert_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vert), &vert[0], GL_STATIC_DRAW);

  glGenBuffers(1, &vertOffset_);
  glBindBuffer(GL_ARRAY_BUFFER, vertOffset_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * n_, NULL, GL_STREAM_DRAW);

  glGenBuffers(1, &vertColor_);
  glBindBuffer(GL_ARRAY_BUFFER, vertColor_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * n_, NULL, GL_STREAM_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Particle::render(const std::vector<glm::vec4> &vertOffset,
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

  glBindBuffer(GL_ARRAY_BUFFER, vertOffset_);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, vertColor_);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, NULL);

  glVertexAttribDivisor(0, 0);
  glVertexAttribDivisor(1, 1);
  glVertexAttribDivisor(2, 1);

  glDepthMask(GL_FALSE);
  glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, vertOffset.size());
  glDepthMask(GL_TRUE);
  
  glVertexAttribDivisor(0, 0);
  glVertexAttribDivisor(1, 0);
  glVertexAttribDivisor(2, 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
