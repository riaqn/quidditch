#include "Particle.hpp"

class SmokeParticle : public Particle {
  const std::vector<glm::vec4> &vertOffset_;
  const std::vector<glm::vec4> vertColor_;
  const Material &material_;
public:
  SmokeParticle(const size_t num,
                const std::vector<glm::vec4> &vertOffset,
                const glm::vec4 &color,
                const Material &material)
    :Particle(num),
     vertOffset_(vertOffset),
     vertColor_(num, color),
     material_(material) {}
  
  virtual void render(MaterialSetter ms) const {
    ms(material_);
    renderHelper(vertOffset_, vertColor_);
  }
};
