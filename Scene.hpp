#include <vector>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "View.hpp"
#include "Projection.hpp"
#include "Renderable.hpp"
#include "Light.hpp"

class Scene {
 private:
  std::vector<Renderable *> vector_;
  const Light &light_;
  const View &view_;
  const Projection &projection_;
  GLuint program_;
 public:
  Scene(const View &view, const Projection &projection, const Light &light);
  void render();
  void attach(Renderable * renderable);
};
