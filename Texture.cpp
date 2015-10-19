#include <Magick++.h>
#include "Texture.hpp"

#include <GL/glew.h>

Texture::Texture(const GLenum target, const std::string &path)
  :target_(target) {
  Magick::Image image(path);
  Magick::Blob blob;
  image.write(&blob, "RGBA");

  glGenTextures(1, &texture_);
  glBindTexture(target, texture_);
  glTexImage2D(target, 0, GL_RGBA, image.columns(), image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, blob.data());

  glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
  glBindTexture(target, 0);
}

void Texture::bind(const GLenum unit) const {
  glActiveTexture(unit);
  glBindTexture(target_, texture_);
}
