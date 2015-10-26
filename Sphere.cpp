#include <vector>
#include <map>
#include <utility>
#include "Sphere.hpp"
#include <glm/glm.hpp>

void Sphere::evolve(std::vector<glm::vec3> &v, std::vector<glm::uvec3> &i, std::vector<glm::vec2> &uv) {
  std::map<std::pair<unsigned, unsigned>, unsigned> MPcache;
  
  auto getMP = [&MPcache, &v, &uv](unsigned a, unsigned b) -> unsigned {
    if (a > b)
      std::swap(a, b);
    std::map<std::pair<unsigned, unsigned>, unsigned>::iterator iter = MPcache.find(std::make_pair(a, b));
    unsigned c;
    if (iter == MPcache.end()) {
      //not in cache, generate a new middle point
      glm::vec3 mp = glm::normalize(v[a] + v[b]);
      v.push_back(mp);
      c = v.size() - 1;
      MPcache.insert({std::make_pair(a, b), c});
      
      glm::vec2 uv0 = (uv[a] + uv[b]) * 0.5f;
      uv.push_back(uv0);
    } else {
      c = iter->second;
    }
    return c;
  };

  i.reserve(i.size() * 4);
  auto end = i.end();
  for (auto iter = i.begin(); iter != end; ++iter) {
    unsigned a = iter->x, b = iter->y, c = iter->z;
    unsigned ab = getMP(a, b);
    unsigned bc = getMP(b, c);
    unsigned ca = getMP(c, a);

    *iter = glm::uvec3(ab, bc, ca);

    i.push_back(glm::uvec3(a, ab, ca));
    i.push_back(glm::uvec3(b, bc, ab));
    i.push_back(glm::uvec3(c, ca, bc));
  }
}

Sphere::Sphere() {
  float phi = 1 / sqrt(2);
  glm::vec3 v[] = {
    glm::vec3(-1, 0, -phi),
    glm::vec3(1, 0, -phi),
    glm::vec3(0, -1, phi ),
    glm::vec3(0, 1, phi),
  };
  std::vector<glm::vec3> v_(v, v + 4);
  
  glm::uvec3 i[] = {glm::uvec3(0, 3, 1),
                    glm::uvec3(0, 2, 3),
                    glm::uvec3(3, 2, 1),
                    glm::uvec3(2, 0, 1)
  };
  std::vector<glm::uvec3> i_(i, i + 4);

  glm::vec2 uv[] = {glm::vec2(0, 0),
                    glm::vec2(0, 0.1),
                    glm::vec2(0.1, 0),
                    glm::vec2(0.1, 0.1)};
  std::vector<glm::vec2> uv_(uv, uv + 4);

  for (auto i = v_.begin(); i != v_.end(); ++i) {
    *i = glm::normalize(*i);
  }

  for (int j = 0; j < 4; ++j)
    evolve(v_, i_, uv_);

  count_ = i_.size() * 3;

  glGenBuffers(1, &VBO_);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, v_.size() * sizeof(v_[0]), v_.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &IBO_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_.size() * sizeof(i_[0]), i_.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glGenBuffers(1, &UV_);
  glBindBuffer(GL_ARRAY_BUFFER, UV_);
  glBufferData(GL_ARRAY_BUFFER, uv_.size() * sizeof(uv_[0]), uv_.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sphere::render(const GLuint WVP, const glm::mat4 &VP) const {
  glUniformMatrix4fv(WVP, 1, GL_FALSE, &VP[0][0]);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, UV_);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);

  glDrawElements(GL_TRIANGLES, count_, GL_UNSIGNED_INT, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
}
