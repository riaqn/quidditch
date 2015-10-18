#include <vector>
#include <map>
#include <utility>
#include "Ball.hpp"
#include <glm/glm.hpp>

void Ball::evolve(std::vector<glm::vec3> &v, std::vector<glm::uvec3> &i) {
  std::map<std::pair<unsigned, unsigned>, unsigned> MPcache;
  
  auto getMP = [&MPcache, &v](unsigned a, unsigned b) -> unsigned {
    auto MP = [](const glm::vec3 &a, const glm::vec3 &b) -> glm::vec3 {
      glm::vec3 c((a.x + b.x) / 2,
                  (a.y + b.y) / 2,
                  (a.z + b.z) / 2);
      return glm::normalize(c);
    };
      
    if (a > b)
      std::swap(a, b);
    std::map<std::pair<unsigned, unsigned>, unsigned>::iterator iter = MPcache.find(std::make_pair(a, b));
    unsigned c;
    if (iter == MPcache.end()) {
      //not in cache, generate a new middle point
      glm::vec3 mp = MP(v[a], v[b]);
      v.push_back(mp);
      c = v.size() - 1;
      MPcache.insert({std::make_pair(a, b), c});
    } else {
      c = iter->second;
    }
    return c;
  };

  unsigned size = i.size();
  for (unsigned iter = 0; iter < size; ++iter) {
    unsigned a = i[iter].x, b = i[iter].y, c = i[iter].z;
    unsigned ab = getMP(a, b);
    unsigned bc = getMP(b, c);
    unsigned ca = getMP(c, a);

    i[iter] = glm::uvec3(ab, bc, ca);

    i.push_back(glm::uvec3(a, ab, ca));
    i.push_back(glm::uvec3(b, bc, ab));
    i.push_back(glm::uvec3(c, ca, bc));
  }
}

void Ball::normalize(std::vector<glm::vec3> &v) {
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

  for (auto i = v_.begin(); i != v_.end(); ++i) {
    *i = glm::normalize(*i);
  }

  for (int j = 0; j < 2; ++j)
    evolve(v_, i_);

  count_ = i_.size() * 3;

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
  
  glDrawElements(GL_TRIANGLES, count_, GL_UNSIGNED_INT, 0);
    
  glDisableVertexAttribArray(0);
}
