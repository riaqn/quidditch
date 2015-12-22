#include <GL/glew.h>
#include <vector>
#include "Renderable.hpp"
#include "FileTexture.hpp"
#include "Box.hpp"

class Table : public Renderable {
private:
  GLuint vertex_;
  GLuint uv_;
  GLuint index_;
  FileTexture cloth_;
  FileTexture wood_;

  const Box box_;
public:
  Table();
  void render(const GLuint WVP, const glm::mat4 &VP) const ;
};
