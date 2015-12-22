#include <glm/glm.hpp>
#include <vector>
#include "NoiseTexture.hpp"
#include "Log.hpp"


#include <Magick++.h>

NoiseTexture::NoiseTexture(const Noise<float, glm::fvec2> &noise_, const unsigned width, const unsigned height, const glm::fvec4 &co)
  :Texture(GL_TEXTURE_2D)
{
  data_ = new unsigned char[width * height * 4];
  for (unsigned i = 0; i < width; ++i) {
    for (unsigned j = 0; j < height; ++j) {
      glm::fvec2 xy((float)i/width/10,
                     (float)j/height/10);

      unsigned base = (i * height + j) * 4;
      data_[base + 0] = noise_.noise(xy) * co.x * 256;
      data_[base + 1] = noise_.noise(xy) * co.y * 256;
      data_[base + 2] = noise_.noise(xy) * co.z * 256;
      
      data_[base + 3] = 255; //noise_.noise(xy) * co.w * 256;
      //debug << noise_.noise(xy) << "\n";
    }
  }
  Magick::Blob blob(data_, width * height * 4);
  Magick::Image image;
  image.size(std::to_string(width) + "x" + std::to_string(height));
  image.magick("RGBA");
  image.read(blob);

  image.display();
  
  load(width, height, data_);
}

NoiseTexture::~NoiseTexture() {
  delete []data_;
}
