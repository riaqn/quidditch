#pragma  once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shape.hpp"
/*
  Shape has no texture
 */
class PrimitiveShape : public virtual Shape {
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

  PrimitiveShape();
  ~PrimitiveShape();
  void load(const std::vector<Vertex> &vert, const std::vector<Face> &face);

  //just draw the item at the origin point
  //the caller is resposible for setup matrix, texture, etc.
  void render() const;
  virtual void render(Render::ModelSetter ms) const {
    ms(glm::mat4());
    render();
  }
};
