#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <GL/glew.h>

class Texture {
public:
  Texture(const GLenum target, const std::string &path);
  ~Texture();
  void bind(const GLenum unit) const;
private:
  GLuint texture_;
  GLenum target_;
};

#endif
