#include "Particle.hpp"

#include <GL/glew.h>
#include <vector>
#include <BulletDynamics/Dynamics/btRigidBody.h>

class BulletParticle : public Particle {
private:
  GLuint vert_;
  GLuint vertOffset_;
  GLuint vertNormal_;
  GLuint vertColor_;

  const std::vector<btRigidBody *> &particles_;
  const size_t n_;

  const Material &material_;
  
public:
  BulletParticle(const std::vector<btRigidBody *> &particles,
                 const std::vector<glm::vec4> &colors,
                 const Material &material);
  virtual void render(MaterialSetter ts) const;
};
