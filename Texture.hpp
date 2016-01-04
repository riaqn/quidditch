#pragma once

#include <string>
#include <GL/glew.h>

class Texture {
public:
  Texture(const GLenum unit,
          const GLenum target);

  Texture(const Texture &texture_) = delete;
  ~Texture();
  void load(const unsigned width,
            const unsigned height,
            const void *const data);
  void bind() const;
private:
  GLuint texture_;
  GLenum target_;
  GLenum unit_;
};


