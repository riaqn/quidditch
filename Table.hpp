#include <GL/glew.h>
#include <vector>
#include "Renderable.hpp"
#include "Texture.hpp"
#include "Box.hpp"

class Table : public Renderable {
private:
  GLuint vertex_;
  GLuint uv_;
  GLuint index_;
  Texture cloth_;
  Texture wood_;

  const Box box_;
public:
  Table();
  void render(const GLuint WVP, const glm::mat4 &VP) const ;
};
