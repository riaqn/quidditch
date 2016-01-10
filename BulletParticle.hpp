#include "Particle.hpp"

#include <GL/glew.h>
#include <vector>
#include "GroupController.hpp"
#include <memory>

class BulletParticle : public Particle {
private:
  const GroupController::Group &particles_;
  const std::vector<glm::vec4> &colors_;

  const Material &material_;
public:
  BulletParticle(const GroupController::Group &particles,
                 const std::vector<glm::vec4> &colors,
                 const Material &material);
  virtual void render(MaterialSetter ts) const;
};
