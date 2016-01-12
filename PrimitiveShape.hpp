#pragma  once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shape.hpp"
/*
  Shape has no texture
 */
class PrimitiveShape : public virtual Shape {
  GLuint vertex_;
  GLuint uv_;
  GLuint triangle_;

  mutable size_t faces_;
public:
  struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
  };

  typedef glm::vec2 UV;
  typedef glm::uvec3 Triangle;

  PrimitiveShape();
  ~PrimitiveShape();
  void load(const std::vector<Vertex> &vert, GLenum usage = GL_STATIC_DRAW) const ;
  void load(const std::vector<UV> &uv, GLenum usage = GL_STATIC_DRAW) const ;
  void load(const std::vector<Triangle> &face, GLenum usage = GL_STATIC_DRAW) const ;

  //just draw the item at the origin point
  //the caller is resposible for setup matrix, texture, etc.
  void render() const;
  virtual void render(Render::ModelSetter ms) const {
    ms(glm::mat4());
    render();
  }
};
