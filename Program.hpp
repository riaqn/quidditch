#pragma once
#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class Program {
  GLuint program_;
public:
  Program(const std::string &vertex_file_path,const std::string &fragment_file_path);
  void use() const ;
  GLuint getUniformLocation(const std::string &var) const ;
  void uniform3fv(const std::string &var, const glm::fvec3 &data) const ;
  void uniform4fv(const std::string &var, const glm::fvec4 &data) const ;
  void uniform1i(const std::string &var, const int data) const;
  void uniform1f(const std::string &var, const float data) const;
  void uniformMatrix4fv(const std::string &var, const glm::fmat4 &data) const;
};
