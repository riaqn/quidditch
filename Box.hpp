#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

#include "Shape.hpp"

class Box : public Shape {
private:
  GLuint v_; //vertices
  GLuint i_; //indexes
  GLuint uv_; //texture coord
public:
  Box();
  virtual void draw() const;
};
