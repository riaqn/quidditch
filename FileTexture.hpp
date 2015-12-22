#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <GL/glew.h>
#include "Texture.hpp"

class FileTexture : public Texture {
public:
  FileTexture(const std::string &path);
};

#endif
