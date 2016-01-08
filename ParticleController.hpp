#include "GroupController.hpp"
#include <random>

class ParticleController : public GroupController {
  const float halflife_;
  static const short particleFilter = 64;
  static std::random_device dev_;
  static std::default_random_engine eng_;
  static std::uniform_real_distribution<float> dist_;
public:
  ParticleController(const float halflife)
    : halflife_(halflife) {};
  
  virtual bool control(const float elapsed,
                        RemoveCallback cb);
  virtual void init(AddCallback cb);
};
