#include "Scene.hpp"
#include "loadShader.hpp"

Scene::Scene(const View &view, const Projection &projection)
  :view_(view), projection_(projection) {
  program_ = LoadShaders("shader.vert", "shader.frag");
  WVP_ = glGetUniformLocation(program_, "WVP");
}

void Scene::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glUseProgram(program_);

  glm::mat4 VP = projection_.matrix() * view_.matrix();
  for (Renderable *r : vector_)
  r->render(WVP_, VP);
}

void Scene::attach(Renderable *renderable) {
  vector_.push_back(renderable);
}

