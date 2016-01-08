#include "Square.hpp"

Square::Square() {
  glm::vec3 position[] = {
    glm::vec3(-1, 0, -1),
    glm::vec3(1, 0, -1),
    glm::vec3(-1, 0, 1),
    glm::vec3(1, 0, 1)
  };

  glm::vec2 uv[] = {
    glm::vec2(0, 0),
    glm::vec2(1, 0),
    glm::vec2(0, 1),
    glm::vec2(1, 1)
  };

  std::vector<glm::uvec3> faces({
      glm::uvec3(0, 3, 1),
        glm::uvec3(0, 2, 3)
        });

  std::vector<Vertex> vert;
  for (auto i = 0; i < 8; ++i)
    vert.push_back(Vertex{position[i], uv[i], glm::vec3(0, 1, 0)});

  load(vert, faces);
}
