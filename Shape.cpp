#include <GL/glew.h>
#include <cstddef>
#include "Shape.hpp"
#include "Log.hpp"

Shape::Shape() {
  glGenBuffers(1, &VBO_);
  glGenBuffers(1, &IBO_);
}

void Shape::load(const std::vector<Vertex> &vert, const std::vector<Face> &face) {

  faces_ = face.size();

  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(vert[0]), vert.data(), GL_STATIC_DRAW);


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, face.size() * sizeof(face[0]), face.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Shape::draw() const {
  error << "draw() " << faces_ << " faces\n";
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, position));
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, uv));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, normal));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
  glDrawElements(GL_TRIANGLES, faces_ * 3, GL_UNSIGNED_INT, 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



