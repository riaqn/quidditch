#include "Texture.hpp"

#include <GL/glew.h>
#include "Log.hpp"

Texture::Texture(const GLenum unit,
                 const GLenum target)
  :unit_(unit), target_(target) {
  glGenTextures(1, &texture_);
}

void Texture::load(const unsigned width,
                   const unsigned height,
                   const void *const data) {
  glTexImage2D(target_, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

Texture::~Texture()
{
  glDeleteTextures(1, &texture_);
}

void Texture::bind() const {
  glActiveTexture(unit_);
  glBindTexture(target_, texture_);
  glTexParameterf(target_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(target_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
