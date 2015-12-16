#ifndef WAVE_HPP
#define WAVE_HPP

#include <GL/glew.h>
#include "Shape.hpp"
#include "Bezier.hpp"
class Wave : public Shape {
public:
  enum Type {
    WAVE_BEZIER,
    WAVE_TRIANGLE
  };
  Wave(int wSample, int hSample, Type type);
  virtual void draw() const;
private:
  unsigned n, m;
  Bezier *bezier;
  GLuint v_, uv_, i_;
  int wSample, hSample;
  static float t_;
  std::vector<std::vector<float> > base;
  Type type_;
};

#endif
