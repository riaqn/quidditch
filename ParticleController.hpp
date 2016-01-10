#include "GroupController.hpp"
#include <random>

class ParticleController : public GroupController {
  const float halflife_;
  static const short particleFilter = 64;
public:
  ParticleController(const float halflife)
    : halflife_(halflife) {};
  
  virtual bool control(const float elapsed);
  virtual void init(WorldProxy &world);
};
