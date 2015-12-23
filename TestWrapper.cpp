#include "TestWrapper.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>

TestWrapper::TestWrapper()
  :texture_("res/blue.png") {}

void TestWrapper::render(ModelSetter ms, TextureSetter ts) const {
  ms(glm::mat4());
  ts(0);

  texture_.bind(GL_TEXTURE0);

  sphere.draw
}
