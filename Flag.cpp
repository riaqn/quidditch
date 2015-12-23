#include <glm/glm.hpp>
#include "Flag.hpp"
Flag::Flag(const Wave &wave, const Texture &texture)
  :wave_(wave), texture_(texture)
{
}
void Flag::render(ModelSetter ms, TextureSetter ts) const {
  ms(glm::mat4(1));

  texture_.bind(GL_TEXTURE0);
  ts(0);
  wave_.draw();
}
