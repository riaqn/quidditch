#include "SoftBodyShape.hpp"
#include "Log.hpp"

void SoftBodyShape::render(Render::ModelSetter ms) const {
  ms(glm::mat4());
  auto &nodes(sb_.m_nodes);
  auto &links(sb_.m_links);
  auto &faces(sb_.m_faces);
  /*
  debug << "nodes.size = " << nodes.size() << '\n';
  debug << "faces.size = " << faces.size() << '\n';
  */
  
  {
    std::vector<Vertex> vertex;
    for (auto i = 0; i < nodes.size(); ++i) {
      vertex.push_back(Vertex{convert<glm::vec3>(nodes[i].m_x),
            convert<glm::vec3>(nodes[i].m_n)
            });
      //debug << nodes[i].m_x << '\n';
    }
    load(vertex, GL_STREAM_DRAW);
  }
  {
    std::vector<Triangle> triangle;
    for (auto i = 0; i < faces.size(); ++i) {
      auto &face = faces[i].m_n;
      triangle.push_back(Triangle(face[0] - &nodes[0],
                                  face[1] - &nodes[0],
                                  face[2] - &nodes[0]));
    }
    load(triangle);
  }
  PrimitiveShape::render();
}
