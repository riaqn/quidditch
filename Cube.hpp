#include "Shape.hpp"
#include "Square.hpp"

class Cube : Shape {
private:
  const Square square_;
public:
  virtual void render(Render::ModelSetter ms) const ;
};
