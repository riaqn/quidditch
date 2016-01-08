#include "Render.hpp"
#include <string>

class MaterialImporter {
public:
  Render::Material import(const std::string &path);
  Render::Material import(std::istream &is);
};
