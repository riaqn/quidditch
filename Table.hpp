#include <GL/glew.h>
#include "Renderable.hpp"

class Table : public Renderable {
private:
  GLuint VBO_;
  GLuint IBO_;
public:
  Table();
  void render(const GLuint WVP, const glm::mat4 &VP);
};
