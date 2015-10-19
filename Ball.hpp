#ifndef BALL_HPP
#define BALL_HPP

#include <glm/glm.hpp>

struct Ball {
  Ball(float m, float r, const glm::vec3 &pos, const glm::vec3 &v);
  virtual void dumb() {}

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
