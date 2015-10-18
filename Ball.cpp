#include <vector>
#include "Ball.hpp"
#include <glm/glm.hpp>

void Ball::evolve(std::vector<glm::vec3> &v, std::vector<glm::uvec3> &i, const unsigned year) {
}

void Ball::normalize(std::vector<glm::vec3> &v) {
  for (auto i = v.begin(); i != v.end(); ++i) {
    float x = (*i)[0];
    float y = (*i)[1];
    float z = (*i)[2];
    
    float l = sqrt(x * x + y * y + z * z);
    (*i) = glm::vec3(x / l, y / l, z / l);
  }
}

Ball::Ball() {
  
  float phi = (1 + sqrt(5)) / 2;
  glm::vec3 v[12] = {
    glm::vec3(-1, phi, 0),
    glm::vec3(1, phi, 0),
    glm::vec3(-1, -phi, 0),
    glm::vec3(1, -phi, 0),

    glm::vec3(0, -1, phi),
    glm::vec3(0, 1, phi),
    glm::vec3(0, -1, -phi),
    glm::vec3(0, 1, -phi),
    
    glm::vec3(phi, 0, -1),
    glm::vec3(phi, 0, 1),
    glm::vec3(-phi, 0, -1),
    glm::vec3(-phi, 0, 1)
  };

  std::vector<glm::vec3> v_(v, v + 12);
  
  glm::uvec3 i[] = {glm::uvec3(0, 11, 5),
                    glm::uvec3(0, 5, 1),
                    glm::uvec3(0, 1, 7),
                    glm::uvec3(0, 7, 10),
                    glm::uvec3(0, 10, 11),
                    
                    glm::uvec3(1, 5, 9),
                    glm::uvec3(5, 11, 4),
                    glm::uvec3(11, 10, 2),
                    glm::uvec3(10, 7, 6),
                    glm::uvec3(7, 1, 8),
                      
                    glm::uvec3(3, 9, 4),
                    glm::uvec3(3, 4, 2),
                    glm::uvec3(3, 2, 6),
                    glm::uvec3(3, 6, 8),
                    glm::uvec3(3, 8, 9),
                      
                    glm::uvec3(4, 9, 5),
                    glm::uvec3(2, 4, 11),
                    glm::uvec3(6, 2, 10),
                    glm::uvec3(8, 6, 7),
                    glm::uvec3(9, 8, 1)};

  std::vector<glm::uvec3> i_(i, i + 20);

  normalize(v_);
  
  evolve(v_, i_, 3);

  glGenBuffers(1, &VBO_);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, v_.size() * sizeof(v_[0]), v_.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &IBO_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_.size() * sizeof(i_[0]), i_.data(), GL_STATIC_DRAW);
}

void Ball::render(const GLuint WVP, const glm::mat4 &VP) {
  glUniformMatrix4fv(WVP, 1, GL_FALSE, &VP[0][0]);

  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
  
  glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_INT, 0);
    
  glDisableVertexAttribArray(0);
}
