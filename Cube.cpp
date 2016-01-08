#include "Cube.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

void Cube::render(Render::ModelSetter ms) const {
  glm::vec3 trans(0, 1, 0);
  float pi2 = glm::pi<float>() / 2;
  ms(glm::translate(glm::rotate(glm::mat4(), pi2 * 0, glm::vec3(0, 0, 1)), trans));
  square_.render();
  ms(glm::translate(glm::rotate(glm::mat4(), pi2 * 1, glm::vec3(0, 0, 1)), trans));
  square_.render();
  ms(glm::translate(glm::rotate(glm::mat4(), pi2 * 2, glm::vec3(0, 0, 1)), trans));
  square_.render();
  ms(glm::translate(glm::rotate(glm::mat4(), pi2 * 3, glm::vec3(0, 0, 1)), trans));
  square_.render();
  ms(glm::translate(glm::rotate(glm::mat4(), pi2 * 1, glm::vec3(1, 0, 0)), trans));
  square_.render();
  ms(glm::translate(glm::rotate(glm::mat4(), pi2 * 3, glm::vec3(1, 0, 0)), trans));
  square_.render();
}
