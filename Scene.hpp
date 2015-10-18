#include <vector>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "View.hpp"
#include "Projection.hpp"
#include "Renderable.hpp"

class Scene {
 private:
  std::vector<Renderable *> vector_;
  const View &view_;
  const Projection &projection_;
  GLuint WVP_;
  GLuint program_;
 public:
  Scene(const View &view, const Projection &projection);
  void render();
  void attach(Renderable * renderable);
};
