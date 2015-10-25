#include <iostream>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <Magick++.h>

#include <glm/glm.hpp>

#include "Table.hpp"
#include "Log.hpp"


Table::Table() {
  glm::vec3 v[4] = {
    glm::vec3(-1.0f, 0.0f, -2.0),
    glm::vec3(-1.0f, 0.0f, 0),
    glm::vec3(1.0f, 0.0f, -2.0f),
    glm::vec3(1.0f, 0.0f, 0.0f)
  };

  glGenBuffers(1, &vertex_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

  glm::vec2 uv[4] = {
    glm::vec2(0, 0),
    glm::vec2(0, 1),
    glm::vec2(1, 0),
    glm::vec2(1, 1)
  };

  glGenBuffers(1, &uv_);
  glBindBuffer(GL_ARRAY_BUFFER, uv_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glm::uvec3 index[2] = { glm::uvec3(0, 1, 2),
                          glm::uvec3(3, 2, 1)
  };
  
  glGenBuffers(1, &index_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  //now loading the texture
  Magick::Image image("res/table.jpg");
  Magick::Blob blob;
  image.write(&blob, "RGBA");

  glGenTextures(1, &texture_);
  glBindTexture(GL_TEXTURE_2D, texture_);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.columns(), image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, blob.data());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
  glBindTexture(GL_TEXTURE_2D, 0);
}
  
void Table::render(const GLuint WVP, const glm::mat4 &VP) const {
  glUniformMatrix4fv(WVP, 1, GL_FALSE, &VP[0][0]);
  
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  
  glBindBuffer(GL_ARRAY_BUFFER, uv_);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
    
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_);

  glBindTexture(GL_TEXTURE_2D, texture_);
  
  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
}
  
