#pragma  once
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <vector>
/*
  Shape has no texture
 */
class Shape {
  GLuint VBO_;
  GLuint IBO_;
  unsigned faces_;
public:
  struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
  };

  typedef glm::uvec3 Face;

  Shape();
  void load(const std::vector<Vertex> &vert, const std::vector<Face> &face);

  //just draw the item at the origin point
  //the caller is resposible for setup matrix, texture, etc.
  void draw() const;
};

