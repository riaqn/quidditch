#pragma once

#include <glm/glm.hpp>

#include "Noise.hpp"
#include "Texture.hpp"

class NoiseTexture : public Texture {
public:
  NoiseTexture(const Noise<float, glm::fvec2> &noise_, const unsigned width, const unsigned height, const glm::vec4 &co);
  ~NoiseTexture();
private:
  unsigned char *data_;
};
