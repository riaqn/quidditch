#include <GL/glew.h>
#include "Renderable.hpp"
#include "Texture.hpp"

class Table : public Renderable {
private:
  GLuint vertex_;
  GLuint uv_;
  GLuint index_;
  GLuint index__;
  Texture cloth_;
  Texture wood_;
public:
  Table();
  void render(const GLuint WVP, const glm::mat4 &VP) const ;
};
