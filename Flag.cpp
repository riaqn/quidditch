#include <glm/glm.hpp>
#include "Flag.hpp"
Flag::Flag(const Wave &wave, const Texture &texture)
  :wave_(wave), texture_(texture)
{
}
void Flag::render(ModelSetter ms, MaterialSetter ts) const {
  ms(glm::mat4(1));

  ts(Material{texture_, 0, glm::vec3(0)});
  wave_.draw();
}
