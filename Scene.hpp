#pragma once
#include <set>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "View.hpp"
#include "Projection.hpp"
#include "Renderable.hpp"
#include "Particle.hpp"
#include "Light.hpp"
#include "Program.hpp"

class Scene {
 private:
  std::set<const Renderable *> renderables_;
  std::set<const Light *> lights_;
  std::set<const Particle *> particles_;
  const View &view_;
  const Projection &projection_;
  const Program program_, program_particle_;
 public:
  Scene(const View &view, const Projection &projection);
  void render();
  void add(const Renderable *const renderable) {
    renderables_.insert(renderable);
  }
    
  void add(const Light *const light) {
    lights_.insert(light);
  }
  
  void add(const Particle *const particle) {
    particles_.insert(particle);
  }

  bool remove(const Renderable *const renderable) {
    return renderables_.erase(renderable) == 1;
  }

  bool remove(const Light *const light) {
    return lights_.erase(light) == 1;
  }
  
  bool remove(const Particle *const particle) {
    return particles_.erase(particle) == 1;
  }


};
