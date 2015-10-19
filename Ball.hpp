#ifndef BALL_HPP
#define BALL_HPP

#include <glm/glm.hpp>

struct Ball {
  //quality
  float m;
  //radius
  float r;
  //position
  glm::vec3 pos;
  //speed
  glm::vec3 v;
};

#endif
