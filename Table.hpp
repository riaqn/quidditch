#include <GL/glew.h>
#include <vector>
#include "Renderable.hpp"
#include "FileTexture.hpp"
#include "Box.hpp"

class Table : public Renderable {
private:
  FileTexture cloth_;
  FileTexture wood_;
  const Box box_;
public:
  Table();
  void render(ModelSetter ms, TextureSetter ts) const ;
};
