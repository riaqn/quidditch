#include "Renderable.hpp"
#include <string>

class MaterialImporter {
public:
  Renderable::Material import(const std::string &path);
  Renderable::Material import(std::istream &is);
};
