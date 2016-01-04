#pragma once

#include <glm/glm.hpp>

#include "Noise.hpp"
#include "Texture.hpp"

class NoiseTexture : public Texture {
public:
  NoiseTexture(const GLenum unit, const Noise<float, glm::fvec2> &noise_, const unsigned width, const unsigned height, const glm::vec4 &a, const glm::vec4 &b);
  ~NoiseTexture();
private:
  unsigned char *data_;
};
