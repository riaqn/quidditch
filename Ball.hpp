#ifndef BALL_HPP
#define BALL_HPP

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct Ball {
  Ball(float m, float r, const glm::vec3 &pos, const glm::vec3 &v, const std::string &name = "UNAMED");
  virtual void dumb() {}

  //quality
  float m;
  //radius
  float r;
  //position
  glm::vec3 x;
  //speed
  glm::vec3 v;

  //orientation
  glm::quat q;

  std::string name;
};

#endif
