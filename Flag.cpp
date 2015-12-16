#include <glm/glm.hpp>
#include "Flag.hpp"
Flag::Flag(const Wave &wave, const Texture &texture)
  :wave_(wave), texture_(texture)
{
}
void Flag::render(const GLuint WVP, const glm::mat4 &VP) const {
  glUniformMatrix4fv(WVP, 1, GL_FALSE, &VP[0][0]);

  texture_.bind(GL_TEXTURE0);
  wave_.draw();
}
