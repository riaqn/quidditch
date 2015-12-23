#include "Box.hpp"

using namespace glm;
using namespace std;

Box::Box() {
  glm::vec3 position[] = {
    glm::vec3(-1.0, -1, -1), //0
    glm::vec3(-1, -1, 1), //1
    glm::vec3(-1, 1, 1), //2
    glm::vec3(-1, 1, -1), //3
    glm::vec3(1, -1, -1), //4
    glm::vec3(1, -1, 1), //5
    glm::vec3(1, 1, 1), //6 
    glm::vec3(1, 1, -1), //7
  };

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
  
  vector<glm::uvec3> faces({
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
      });

  vector<Vertex> vert;
  for (auto i = 0; i < 8; ++i)
    vert.push_back(Vertex{position[i], uv[i], position[i]});

  load(vert, faces);
}
