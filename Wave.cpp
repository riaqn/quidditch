#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Wave.hpp"
float Wave::t_ = 0;
Wave::Wave(int wSample, int hSample)
  :wSample(wSample), hSample(hSample) {
  glm::vec3 v[wSample][hSample];
  glGenBuffers(1, &v_);
  glBindBuffer(GL_ARRAY_BUFFER, v_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_DYNAMIC_DRAW);

  glm::fvec2 uv[wSample][hSample];
  for (int i = 0; i < wSample; ++i)
    for (int j = 0; j < hSample; ++j)
      uv[i][j] = glm::fvec2((float)i / wSample, (float)j / hSample);
  glGenBuffers(1, &uv_);
  glBindBuffer(GL_ARRAY_BUFFER, uv_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);

  glm::uvec3 idx[wSample - 1][hSample - 1][2];
  for (int i = 0; i < wSample - 1; ++i)
    for (int j = 0; j < hSample - 1; ++j) {
      idx[i][j][0] = glm::uvec3(i * hSample + j, (i + 1) * hSample + j, i * hSample + (j + 1));
      idx[i][j][1] = glm::uvec3(i * hSample + (j + 1), (i + 1) * hSample + j, (i + 1) * hSample + j + 1);
    }

  glGenBuffers(1, &i_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Wave::draw() const {
  t_ += 1.0/60;
    glm::vec3 v[wSample][hSample];
    for (int i = 0; i < wSample; ++i)
    for (int j = 0; j < hSample; ++j) {
      v[i][j] = glm::vec3(-1 + 2.0 * i / wSample,
                          -1 + 2.0 * j / hSample,
                          sin(((float)i / wSample + (float)j / hSample + t_)* 10) / 10);
    }
    glBindBuffer(GL_ARRAY_BUFFER, v_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(v), v);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, uv_);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_);
    glDrawElements(GL_TRIANGLES, (hSample - 1) * (wSample - 1) * 2 * 3, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
