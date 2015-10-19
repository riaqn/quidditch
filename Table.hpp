#include <GL/glew.h>
#include "Renderable.hpp"

class Table : public Renderable {
private:
  GLuint vertex_;
  GLuint uv_;
  GLuint index_;
  GLuint texture_;
public:
  Table();
  void render(const GLuint WVP, const glm::mat4 &VP);
};
