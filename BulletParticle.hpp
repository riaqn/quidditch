#include "Particle.hpp"

#include <GL/glew.h>
#include <vector>
#include "GroupController.hpp"
#include <memory>

class BulletParticle : public Particle {
private:
  const GroupController::Group &particles_;
  const std::vector<glm::vec4> &vertColor_;

  const Material &material_;

  const float size_;
public:
  BulletParticle(const size_t num,
                 const GroupController::Group &particles,
                 const std::vector<glm::vec4> &vertColor,
                 const Material &material,
                 const float size)
    :Particle(num),
     particles_(particles),
     vertColor_(vertColor),
     material_(material),
     size_(size) {}
  virtual void render(MaterialSetter ts) const;
};
