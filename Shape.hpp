#pragma once
#include "Render.hpp"

class Shape {
public:
  virtual void render(Render::ModelSetter ms) const = 0;
};
