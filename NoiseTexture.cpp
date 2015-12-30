#include <glm/glm.hpp>
#include <vector>
#include "NoiseTexture.hpp"
#include "Log.hpp"
#include <Magick++.h>

NoiseTexture::NoiseTexture(const Noise<float, glm::fvec2> &noise_, const unsigned width, const unsigned height, const glm::fvec4 &a, const glm::fvec4 &b)
  :Texture(GL_TEXTURE_2D)
{
  data_ = new unsigned char[width * height * 4];
  for (unsigned i = 0; i < width; ++i) {
    for (unsigned j = 0; j < height; ++j) {
      glm::fvec2 xy((float)i/width/10,
                     (float)j/height/10);

      unsigned base = (i * height + j) * 4;
      float noise = noise_.noise(xy);
      for (unsigned k = 0; k < 4; ++k)
      data_[base + k] = a[k] + noise * (b[k] - a[k]);
    }
  }
  Magick::Blob blob(data_, width * height * 4);
  Magick::Image image;
  image.size(std::to_string(width) + "x" + std::to_string(height));
  image.magick("RGBA");
  image.read(blob);

  static int count = 0;
  image.write("noise" + std::to_string(count++) + ".png");
  
  load(width, height, data_);
}

NoiseTexture::~NoiseTexture() {
  delete []data_;
}
