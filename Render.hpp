#pragma  once
#include <glm/glm.hpp>
#include <functional>
#include "Texture.hpp"

class Render {
public:
  struct Material {
    const Texture *texture;
    float shininess;
    glm::vec3 specularColor;
    float brightness;
  };
  typedef std::function<void (const glm::mat4 &)> ModelSetter;
  typedef std::function<void (const Material &)> MaterialSetter;
  virtual void render(ModelSetter ms, MaterialSetter ts) const = 0;
};

