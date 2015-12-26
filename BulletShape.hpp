#pragma once
#include <glm/glm.hpp>
#include <functional>
class BulletShape {
public:
  typedef std::function<void (const glm::vec3 &)> ScaleSetter;
  virtual void draw(ScaleSetter ss) const = 0;
};
