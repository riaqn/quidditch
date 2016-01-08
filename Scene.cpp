#include "Scene.hpp"
#include "Log.hpp"

Scene::Scene(const View &view, const Projection &projection)
  :view_(view), projection_(projection),
   program_("shader.vert", "shader.frag"),
   program_particle_("shader_particle.vert",
                     "shader_particle.frag") {
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

  program_.uniform3fv("cameraPosition", view_.eye);

  program_.uniformMatrix4fv("camera", projection_.matrix() * view_.matrix());

  size_t i = 0;
  program_.uniform1i("numLights", lights_.size());
  for (auto it = lights_.begin(); it != lights_.end(); ++it, ++i) {
    auto light = *it;
    std::string pre = "allLights[" + std::to_string(i) + "].";
    program_.uniform4fv(pre + "position", light->getPosition());
    program_.uniform3fv(pre + "intensities", light->getIntensities());
    program_.uniform1f(pre + "attenuation", light->getAttenuation());
    program_.uniform1f(pre + "ambientCoefficient", light->getAmbientCoefficient());
    program_.uniform1f(pre + "coneAngle", light->getConeAngle());
    program_.uniform3fv(pre + "coneDirection", light->getConeDirection());
  }

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  const Program &program = program_;
  for (auto r : renderables_)
    r->render([&program](const glm::mat4 & m) -> void {
        program.uniformMatrix4fv("model", m);
      }, [&program](const Render::Material &m) -> void {
        m.texture->bind();
        program.uniform1i("materialTex", m.texture->unit_ - GL_TEXTURE0);
        program.uniform1f("materialShininess", m.shininess);
        program.uniform3fv("materialSpecularColor", m.specularColor);
      });

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);

  program_particle_.use();

  program_particle_.uniform3fv("cameraPosition", view_.eye);

  program_particle_.uniformMatrix4fv("camera", projection_.matrix() * view_.matrix());

  program_particle_.uniform1i("numLights", lights_.size());
  i = 0;
  for (auto it = lights_.begin(); it != lights_.end(); ++it, ++i) {
    auto light = *it;
    std::string pre = "allLights[" + std::to_string(i) + "].";
    program_particle_.uniform4fv(pre + "position", light->getPosition());
    program_particle_.uniform3fv(pre + "intensities", light->getIntensities());
    program_particle_.uniform1f(pre + "attenuation", light->getAttenuation());
    program_particle_.uniform1f(pre + "ambientCoefficient", light->getAmbientCoefficient());
    program_particle_.uniform1f(pre + "coneAngle", light->getConeAngle());
    program_particle_.uniform3fv(pre + "coneDirection", light->getConeDirection());
  }

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  

  const Program &program_particle = program_particle_;
  for (auto p : particles_)
    p->render([&program_particle](const Particle::Material &m) -> void {
        program_particle.uniform1f("materialShininess", m.shininess);
        program_particle.uniform3fv("materialSpecularColor", m.specularColor);
      });

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
}
