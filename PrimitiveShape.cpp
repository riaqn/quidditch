#include <GL/glew.h>
#include <cstddef>
#include "PrimitiveShape.hpp"
#include "Log.hpp"

PrimitiveShape::PrimitiveShape() {
  glGenBuffers(1, &vertex_);
  glGenBuffers(1, &uv_);
  glGenBuffers(1, &triangle_);
}

void PrimitiveShape::load(const std::vector<Vertex> &vert, GLenum usage) const {
  glBindBuffer(GL_ARRAY_BUFFER, vertex_);
  glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(vert[0]), vert.data(), usage);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PrimitiveShape::load(const std::vector<UV> &uv, GLenum usage) const {
  glBindBuffer(GL_ARRAY_BUFFER, uv_);
  glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(uv[0]), uv.data(), usage);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

}
  
void PrimitiveShape::load(const std::vector<Triangle> &triangle, GLenum usage) const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangle.size() * sizeof(triangle[0]), triangle.data(), usage);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  faces_ = triangle.size();
}

PrimitiveShape::~PrimitiveShape() {
  glDeleteBuffers(1, &vertex_);
  glDeleteBuffers(1, &uv_);
  glDeleteBuffers(1, &triangle_);
}

void PrimitiveShape::render() const {
  glBindBuffer(GL_ARRAY_BUFFER, vertex_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, position));
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, normal));

  glBindBuffer(GL_ARRAY_BUFFER, uv_);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_);

  glDrawElements(GL_TRIANGLES, faces_ * 3, GL_UNSIGNED_INT, 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
