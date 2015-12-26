#include <Magick++.h>
#include "Texture.hpp"
#include "FileTexture.hpp"

#include "Log.hpp"

FileTexture::FileTexture(const std::string &path)
  :Texture(GL_TEXTURE_2D) {
  Magick::Image image(path);
  Magick::Blob blob;
  image.write(&blob, "RGBA");

  debug << "loaded texture " << path << " " << image.columns() << 'x' << image.rows() << "\n";
  load(image.columns(), image.rows(), blob.data());
}

FileTexture *FileTexture::get(const std::string &path) {
  auto iter = map_.find(path);
  if (iter == map_.end()) {
    iter = map_.insert(std::make_pair(path, new FileTexture(path))).first;
  }
  return iter->second;
}

std::map<std::string, FileTexture *> FileTexture::map_;
