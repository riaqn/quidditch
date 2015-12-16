#ifndef WAVE_HPP
#define WAVE_HPP

#include <GL/glew.h>
#include "Shape.hpp"
class Wave : public Shape {
private:
  GLuint v_, uv_, i_;
  int wSample, hSample;
  static float t_;
public:
  Wave(int wSample, int hSample);
  virtual void draw() const;
};

#endif
