#include <iostream>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <Magick++.h>

#include <glm/glm.hpp>

#include "Table.hpp"
#include "Log.hpp"
#include "Texture.hpp"


Table::Table()
  : cloth_(GL_TEXTURE_2D, "res/table.jpg"),
    wood_(GL_TEXTURE_2D, "res/wood.jpg") {
  glm::vec3 v[] = {
    glm::vec3(-1.0f, 0.0f, -2.0),
    glm::vec3(-1.0f, 0.0f, 0),
    glm::vec3(1.0f, 0.0f, -2.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),

    glm::vec3(-1.0f, 0.1f, -2.0),
    glm::vec3(-1.0f, 0.1f, 0),
    glm::vec3(1.0f, 0.1f, -2.0f),
    glm::vec3(1.0f, 0.1f, 0.0f)
  };

  glGenBuffers(1, &vertex_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

  glm::vec2 uv[] = {
    glm::vec2(0, 0),
    glm::vec2(0, 1),
    glm::vec2(1, 0),
    glm::vec2(1, 1),

    glm::vec2(1, 1),
    glm::vec2(1, 0),
    glm::vec2(0, 1),
    glm::vec2(0, 0)
  };

  glGenBuffers(1, &uv_);
  glBindBuffer(GL_ARRAY_BUFFER, uv_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glm::uvec3 index[2] = { glm::uvec3(0, 1, 2),
                          glm::uvec3(3, 2, 1)
  };

  glm::uvec3 index_wall[8] = {glm::uvec3(0, 5, 1),
                              glm::uvec3(4, 5, 0),
                              glm::uvec3(3, 7, 6),
                              glm::uvec3(2, 3, 6),
                              glm::uvec3(0, 2, 6),
                              glm::uvec3(4, 0, 6),
                              glm::uvec3(1, 5, 3),
                              glm::uvec3(3, 5, 7)};
  
  glGenBuffers(1, &index_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
  glGenBuffers(1, &index__);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index__);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_wall), index_wall, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
  
void Table::render(const GLuint WVP, const glm::mat4 &VP) const {
  glUniformMatrix4fv(WVP, 1, GL_FALSE, &VP[0][0]);
  
  glBindBuffer(GL_ARRAY_BUFFER, vertex_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  
  glBindBuffer(GL_ARRAY_BUFFER, uv_);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
    
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_);

  cloth_.bind(GL_TEXTURE0);
  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index__);

  wood_.bind(GL_TEXTURE0);
  glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
  
