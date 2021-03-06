#include <iostream>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <Magick++.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Table.hpp"
#include "Log.hpp"
#include "Texture.hpp"

using namespace glm;
Table::Table()
  : cloth_("res/table.jpg"),
    wood_("res/wood.jpg") {
}
  
void Table::render(ModelSetter ms,
                   MaterialSetter ts) const {
  glm::vec3 s;
  glm::mat4 scale;

  ts(Material{cloth_, 100, glm::vec3(0, 0, 0)});
  ms(glm::scale(glm::translate(glm::mat4(), glm::vec3(0, 0, -1)), glm::vec3(1, 0.01, 1)));
  box_.draw();

  ts(Material{wood_, 80, glm::vec3(1, 1, 1)});
  //draw wall
  s = glm::vec3(1.1, 0.05, 0.05);
  ms(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 0, 0.05)), s));
  box_.draw();

  ms(glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, 0, -2.05)), s));
  box_.draw();

  s = glm::vec3(0.05, 0.05, 1);
  ms(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-1.05, 0, -1)), s));
  box_.draw();

  ms(glm::scale(glm::translate(glm::mat4(1), glm::vec3(1.05, 0, -1)), s));
  box_.draw();

  //here comes the legs
  s =  glm::vec3(0.05, 1, 0.05);
  ms(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-1, -1.01, 0)), s));

  box_.draw();

  ms(glm::scale(glm::translate(glm::mat4(1), glm::vec3(1, -1.01, 0)), s));
  box_.draw();

  ms(glm::scale(glm::translate(glm::mat4(1), glm::vec3(-1, -1.01, -2)), s));
  box_.draw();

  ms(glm::scale(glm::translate(glm::mat4(1), glm::vec3(1, -1.01, -2)), s));
  box_.draw();
}
  
