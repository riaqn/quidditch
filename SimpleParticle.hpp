#include "Particle.hpp"

class SimpleParticle : public Particle {
  const std::vector<glm::vec4> &vertOffset_;
  const std::vector<glm::vec4> &vertColor_;
  const Material &material_;
public:
  SimpleParticle(const size_t num,
                const std::vector<glm::vec4> &vertOffset,
                const std::vector<glm::vec4> &vertColor,
                const Material &material)
    :Particle(num),
     vertOffset_(vertOffset),
     vertColor_(vertColor),
     material_(material) {}
  
  virtual void render(MaterialSetter ms) const {
    ms(material_);
    Particle::render(vertOffset_, vertColor_);
  }
};
