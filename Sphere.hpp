#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "Shape.hpp"

class Sphere : public Shape {
private:
  static void evolve(std::vector<glm::vec3> &v, std::vector<glm::uvec3> &i, std::vector<glm::vec2> &uv);
  static void normalize(std::vector<glm::vec3> &v);
public:
  Sphere();
};
