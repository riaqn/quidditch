#include "Texture.hpp"

#include <GL/glew.h>
#include "Log.hpp"

Texture::Texture(const GLenum target)
  :target_(target) {
  glGenTextures(1, &texture_);
}

void Texture::load(const unsigned width,
              const unsigned height,
              const void *const data) {
  glBindTexture(target_, texture_);
  glTexImage2D(target_, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

  glTexParameterf(target_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(target_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
  glBindTexture(target_, 0);
}

Texture::~Texture()
{
  glDeleteTextures(1, &texture_);
}

void Texture::bind(const GLenum unit) const {
  glActiveTexture(unit);
  glBindTexture(target_, texture_);
}
