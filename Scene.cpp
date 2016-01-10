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

void Scene::setLight(Program &program) {
  program.uniform1i("numLights", lights_.size());
  size_t i = 0;
  for (auto light : lights_) {
    Light::Spec spec = (*light)();
    std::string pre = "allLights[" + std::to_string(i) + "].";
    program.uniform4fv(pre + "position", spec.position);
    program.uniform3fv(pre + "intensities", spec.intensities);
    program.uniform1f(pre + "attenuation", spec.attenuation);
    program.uniform1f(pre + "ambientCoefficient", spec.ambientCoefficient);
    program.uniform1f(pre + "coneAngle", spec.coneAngle);
    program.uniform3fv(pre + "coneDirection", spec.coneDirection);
    ++i;
  }
}

void Scene::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  program_.use();

  program_.uniform3fv("cameraPosition", view_.eye);

  program_.uniformMatrix4fv("camera", projection_.matrix() * view_.matrix());
  
  setLight(program_);

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
        program.uniform1f("brightness", m.brightness);
        program.uniform1f("materialShininess", m.shininess);
        program.uniform3fv("materialSpecularColor", m.specularColor);
      });

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);

  program_particle_.use();

  program_particle_.uniform3fv("cameraPosition", view_.eye);
  program_particle_.uniformMatrix4fv("camera", projection_.matrix() * view_.matrix());
  program_particle_.uniform3fv("cameraRight", view_.right);
  program_particle_.uniform3fv("cameraUp", view_.up);

  setLight(program_particle_);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  

  const Program &program_particle = program_particle_;
  for (auto p : particles_)
    p->render([&program_particle](const Particle::Material &m) -> void {
        program_particle.uniform1f("materialShininess", m.shininess);
        program_particle.uniform3fv("materialSpecularColor", m.specularColor);
        program_particle.uniform1f("materialBrightness", m.brightness);
      });

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}
