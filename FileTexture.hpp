#pragma  once

#include <string>
#include <GL/glew.h>
#include "Texture.hpp"
#include <map>

class FileTexture : public Texture {
private:
  static std::map<std::string, FileTexture *> map_;
  FileTexture(const std::string &path);
public:
  static FileTexture *get(const std::string &path);
};



