#include "Render.hpp"
#include "Sphere.hpp"
#include "FileTexture.hpp"
class TestWrapper : public Render {
  Sphere sphere_;
  FileTexture texture_;
public:
  TestWrapper();
  void render(ModelSetter ms, TextureSetter ts) const;
};
