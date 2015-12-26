#include "TriangleMeshShape.hpp"
#include <BulletCollision/CollisionShapes/btStridingMeshInterface.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include "Log.hpp"
#include "utils.hpp"

TriangleMeshShape::TriangleMeshShape(const btTriangleMeshShape *const shape, const int i) {
  std::vector<Shape::Vertex> vert;
  std::vector<Shape::Face> face;
  const btStridingMeshInterface *interface = shape->getMeshInterface();
  
  const unsigned char *v;
  int v_num;
  int v_stride;
  const unsigned char *t;
  int t_num;
  int t_stride;
  PHY_ScalarType v_type;
  PHY_ScalarType t_type;
    
  interface->
    getLockedReadOnlyVertexIndexBase(&v, v_num, v_type, v_stride,
                                     &t, t_stride, t_num, t_type, i);

  notice << "reading " << v_num << " vertices, " << t_num << " triangles\n";
  if (v_type != PHY_FLOAT || t_type != PHY_INTEGER)
    throw std::runtime_error("");
  for (auto j = 0; j < v_num; ++j) {
    glm::vec3 &pos = *(glm::vec3 *)&v[v_stride * j];
    vert.push_back(Shape::Vertex{pos,
          glm::vec2(pos.x, pos.z),
          glm::vec3(0)});
  }
  for (auto j = 0; j < t_num; ++j) {
    glm::ivec3 &tri = *(glm::ivec3 *)&t[t_stride * j];
    face.push_back(tri);
    glm::fvec3 normal = glm::cross(vert[tri[1]].position - vert[tri[0]].position, vert[tri[2]].position - vert[tri[0]].position);
    vert[tri[0]].normal += normal;
    vert[tri[1]].normal += normal;
    vert[tri[2]].normal += normal;
  }

  for (auto j = 0; j < v_num; ++j)
    vert[j].normal = glm::normalize(vert[j].normal);

  for (auto v0 : vert)
    debug << v0.position << v0.uv << v0.normal << '\n';
  for (auto f0 : face)
    debug << f0 << '\n';
  shape_.load(vert, face);
}

void TriangleMeshShape::draw(ScaleSetter ss) const {
  ss(glm::vec3(1));
  shape_.draw();
}
