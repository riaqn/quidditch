#include "Box.hpp"

Box::Box() {
  glm::vec3 v[] = {
    glm::vec3(-1.0, -1, -1),
    glm::vec3(-1, -1, 1),
    glm::vec3(-1, 1, 1),
    glm::vec3(-1, 1, -1),
    glm::vec3(1, -1, -1),
    glm::vec3(1, -1, 1),
    glm::vec3(1, 1, 1),
    glm::vec3(1, 1, -1),
  };
  
  glGenBuffers(1, &v_);
  glBindBuffer(GL_ARRAY_BUFFER, v_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

  glm::vec2 uv[] = {
    glm::vec2(-1.0, -1),
    glm::vec2(-1., 1),
    glm::vec2(1, 1),
    glm::vec2(1, -1),
    glm::vec2(-1, -1),
    glm::vec2( -1, 1),
    glm::vec2( 1, 1),
    glm::vec2( 1, -1),
  };
  
  glGenBuffers(1, &uv_);
  glBindBuffer(GL_ARRAY_BUFFER, uv_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);

  glm::uvec3 i[12] = {
    glm::uvec3(0, 4, 5),
    glm::uvec3(0, 5, 1),
    glm::uvec3(1, 5, 2),
    glm::uvec3(2, 5, 6),
    glm::uvec3(0, 1, 3),
    glm::uvec3(3, 1, 2),
    glm::uvec3(2, 6, 3),
    glm::uvec3(3, 6, 7),
    glm::uvec3(4, 6, 5),
    glm::uvec3(4, 7, 6),
    glm::uvec3(0, 3, 4),
    glm::uvec3(3, 7, 4)
  };

  glGenBuffers(1, &i_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i), i, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Box::draw() const {
  glBindBuffer(GL_ARRAY_BUFFER, v_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, uv_);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_);
  glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
