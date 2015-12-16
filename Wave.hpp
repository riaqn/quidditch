#ifndef WAVE_HPP
#define WAVE_HPP

#include <GL/glew.h>
#include "Shape.hpp"
#include "Bezier.hpp"
class Wave : public Shape {
private:
  unsigned n, m;
  Bezier *bezier;
  GLuint v_, uv_, i_;
  int wSample, hSample;
  static float t_;
  std::vector<std::vector<float> > base;
public:
  Wave(int wSample, int hSample);
  virtual void draw() const;
};

#endif
