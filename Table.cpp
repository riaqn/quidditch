#include <iostream>
#include "Table.hpp"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

Table::Table() {
  sf::Vector3f Vertices[4];
  Vertices[0] = sf::Vector3f(-1.0f, 0.0f, -2.0);
  Vertices[1] = sf::Vector3f(-1.0f, 0.0f, 0);
  Vertices[2] = sf::Vector3f(1.0f, 0.0f, -2.0f);
  Vertices[3] = sf::Vector3f(1.0f, 0.0f, 0.0f);

  glGenBuffers(1, &VBO_);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

  unsigned int Indices[] = { 0, 1, 2,
                             1, 2, 3};
  
  glGenBuffers(1, &IBO_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}
  
void Table::render(const GLuint WVP, const glm::mat4 &VP) {

  glUniformMatrix4fv(WVP, 1, GL_FALSE, &VP[0][0]);
  
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
  glDisableVertexAttribArray(0);
}
  
