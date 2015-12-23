#include <vector>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "View.hpp"
#include "Projection.hpp"
#include "Renderable.hpp"
#include "Light.hpp"
#include "Program.hpp"

class Scene {
 private:
  std::vector<const Renderable *> vector_;
  std::vector<const Light *> lights_;
  const View &view_;
  const Projection &projection_;
  const Program program_;
 public:
  Scene(const View &view, const Projection &projection);
  void render();
  void attach(const Renderable *const renderable);
  void attach(const Light *const light);
};
