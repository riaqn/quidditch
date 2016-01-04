#pragma  once

#include <string>
#include <GL/glew.h>
#include "Texture.hpp"
#include <map>

class FileTexture : public Texture {
private:
  static std::map<std::pair<GLenum, std::string>, FileTexture *> map_;
  FileTexture(const GLenum unit, const std::string &path);
public:
  static FileTexture *get(const GLenum unit,
                          const std::string &path);
};



