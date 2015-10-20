#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Renderable.hpp"
#include "Texture.hpp"
#include <glm/glm.hpp>
#include <vector>

class Sphere : public Renderable {
private:
  GLuint VBO_, IBO_, UV_;
  static void evolve(std::vector<glm::vec3> &v, std::vector<glm::uvec3> &i, std::vector<glm::vec2> &uv);
  static void normalize(std::vector<glm::vec3> &v);
  size_t count_;
public:
  Sphere();
  void render(const GLuint WVP, const glm::mat4 &VP) const ;
};

#endif
