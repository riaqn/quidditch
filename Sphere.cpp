#include <vector>
#include <map>
#include <utility>
#include <functional>
#include "Sphere.hpp"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

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

  std::vector<glm::vec3> v({
      glm::vec3(-1, 0, -phi), //0
        glm::vec3(1, 0, -phi), //1
        glm::vec3(0, -1, phi), //2
        glm::vec3(0, 1, phi), //3
        glm::vec3(0, 1, phi), //4
        glm::vec3(0, 1, phi) //5
        });
  
  std::vector<glm::uvec3> i({
      glm::uvec3(0, 3, 1),
        glm::uvec3(0, 1, 2),
        glm::uvec3(2, 1, 5),
        glm::uvec3(4, 0, 2)
  });

   std::vector<glm::vec2> uv({
       glm::fvec2(0.5, 0.75),
         glm::fvec2(0.5, 0.25),
         glm::fvec2(0, 0.5),
         glm::fvec2(1, 0.5),
         glm::fvec2(0, 1),
         glm::fvec2(0, 0)});
   
  for (auto k = v.begin(); k != v.end(); ++k) {
    *k = glm::normalize(*k);
  }

  for (auto k = 0; k < 4; ++k)
    evolve(v, i, uv);

  vector<Vertex> vert;
  for (auto k = 0; k < v.size(); ++k)
    vert.push_back(Vertex{v[k], uv[k], v[k]});

  load(vert, i);
}
