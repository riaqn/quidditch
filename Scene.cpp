#include "Scene.hpp"
#include "loadShader.hpp"
#include "Log.hpp"

Scene::Scene(const View &view, const Projection &projection, const Light &light)
  :view_(view), projection_(projection), light_(light) {

  program_ = LoadShaders("shader.vert", "shader.frag");
  glActiveTexture(GL_TEXTURE0);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glFrontFace(GL_CCW);
  /*
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  */
}

void Scene::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glUseProgram(program_);

  GLuint T = glGetUniformLocation(program_, "tex");
  GLuint M = glGetUniformLocation(program_, "model");
  
  GLuint VP = glGetUniformLocation(program_, "VP");
  glm::mat4 mat = projection_.matrix() * view_.matrix();
  glUniformMatrix4fv(VP, 1, GL_FALSE, &mat[0][0]);

  GLuint LightPosition = glGetUniformLocation(program_, "light.position");
  glUniform3fv(LightPosition, 1, &light_.position[0]);
  GLuint LightIntensities = glGetUniformLocation(program_, "light.intensities");
  error << LightIntensities << '\n';
  glUniform3fv(LightIntensities, 1, &light_.intensities[0]);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  
  for (Renderable *r : vector_)
    r->render([M](const glm::mat4 & m) -> void {
        error << "-- modelSet -- \n";
        error << m;
        glUniformMatrix4fv(M, 1, GL_FALSE, &m[0][0]);
      }, [T](const GLuint u) -> void {
        error << "-- texSet -- \n";
        error << u << "\n";
        glUniform1i(T, u);
      });

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

void Scene::attach(Renderable *renderable) {
  vector_.push_back(renderable);
}

