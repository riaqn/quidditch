#include <GL/glew.h>
#include <vector>
#include "Render.hpp"
#include "FileTexture.hpp"
#include "Box.hpp"

class Table : public Render {
private:
  FileTexture cloth_;
  FileTexture wood_;
  const Box box_;
public:
  Table();
  void render(ModelSetter ms, MaterialSetter ts) const ;
};
