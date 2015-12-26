#include "Scene.hpp"
#include "Log.hpp"

Scene::Scene(const View &view, const Projection &projection)
  :view_(view), projection_(projection),
   program_("shader.vert", "shader.frag") {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glFrontFace(GL_CCW);
  /*
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  */
}

void Scene::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  program_.use();

  program_.uniform3fv("cameraPosition", view_.eye_);

  program_.uniformMatrix4fv("camera", projection_.matrix() * view_.matrix());

  program_.uniform1i("numLights", lights_.size());
  for (auto i = 0; i < lights_.size(); ++i) {
    std::string pre = "allLights[" + std::to_string(i) + "].";
    program_.uniform4fv(pre + "position", lights_[i]->getPosition());
    program_.uniform3fv(pre + "intensities", lights_[i]->getIntensities());
    program_.uniform1f(pre + "attenuation", lights_[i]->getAttenuation());
    program_.uniform1f(pre + "ambientCoefficient", lights_[i]->getAmbientCoefficient());
    program_.uniform1f(pre + "coneAngle", lights_[i]->getConeAngle());
    program_.uniform3fv(pre + "coneDirection", lights_[i]->getConeDirection());
  }

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  const Program &program = program_;
  for (auto r : vector_)
    r->render([&program](const glm::mat4 & m) -> void {
        program.uniformMatrix4fv("model", m);
      }, [&program](const Renderable::Material &m) -> void {
        m.texture.bind(GL_TEXTURE0);
        program.uniform1i("materialTex", 0);
        program.uniform1f("materialShininess", m.shininess);
        program.uniform3fv("materialSpecularColor", m.specularColor);
      });

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

void Scene::attach(const Renderable *const renderable) {
  vector_.push_back(renderable);
}

void Scene::attach(const Light *const light) {
  lights_.push_back(light);
}

