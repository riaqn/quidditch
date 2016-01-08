#include "MaterialImporter.hpp"
#include "FileTexture.hpp"
#include <fstream>
#include "utils.hpp"

Render::Material MaterialImporter::import(const std::string &path) {
  std::ifstream is(path);
  return import(is);
}

Render::Material MaterialImporter::import(std::istream &is) {
  std::string texture;
  float shininess;
  glm::vec3 specularColor;

  is >> texture >> shininess >> specularColor;
  auto tex = FileTexture::get(GL_TEXTURE0, texture);
  return Render::Material{tex, shininess, specularColor};
}

