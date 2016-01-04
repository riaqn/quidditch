#include <Magick++.h>
#include "Texture.hpp"
#include "FileTexture.hpp"

#include "Log.hpp"

FileTexture::FileTexture(const GLenum unit, const std::string &path)
  :Texture(unit, GL_TEXTURE_2D) {
  Magick::Image image(path);
  Magick::Blob blob;
  image.write(&blob, "RGBA");

  debug << "loaded texture " << path << " " << image.columns() << 'x' << image.rows() << "\n";
  bind();
  load(image.columns(), image.rows(), blob.data());
}

FileTexture *FileTexture::get(const GLenum unit, const std::string &path) {
  auto pair = std::make_pair(unit, path);
  auto iter = map_.find(pair);
  if (iter == map_.end()) {
    iter = map_.insert(std::make_pair(pair, new FileTexture(unit, path))).first;
  }
  return iter->second;
}

std::map<std::pair<GLenum, std::string>, FileTexture *> FileTexture::map_;
