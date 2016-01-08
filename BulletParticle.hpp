#include "Particle.hpp"

#include <GL/glew.h>
#include <vector>
#include "GroupController.hpp"
#include <memory>

class BulletParticle : public Particle {
private:
  GLuint vert_;
  GLuint vertOffset_;
  GLuint vertNormal_;
  GLuint vertColor_;

  const GroupController::Group &particles_;
  const std::vector<glm::vec4> &colors_;
  const size_t n_;

  const Material &material_;
  
public:
  BulletParticle(const GroupController::Group &particles,
                 const std::vector<glm::vec4> &colors,
                 const Material &material);
  ~BulletParticle();
  virtual void render(MaterialSetter ts) const;
};
