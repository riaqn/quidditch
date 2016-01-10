#include "GroupController.hpp"
#include <random>
#include "Noise.hpp"

class SmokeController : public Controller {
private:
  const btRigidBody &rb_;
  const size_t num_;
  size_t off_;
  const float rate_;

  float ts_;
  const glm::vec4 &color_;

  std::vector<glm::vec4> vertOffset_;
  std::vector<glm::vec4> vertColor_;

  const Noise<float, glm::vec3> &noise_;
public:
  SmokeController(const btRigidBody &rb,
                  const size_t num,
                  const float rate,
                  const glm::vec4 &color,
                  const Noise<float, glm::vec3> &noise)
    :rb_(rb), num_(num), off_(0), rate_(rate), color_(color), ts_(0), noise_(noise) {}
  
  virtual bool control(const float elapsed);

  const std::vector<glm::vec4> &getVertOffset() const {
    return vertOffset_;
  }

  const std::vector<glm::vec4> &getVertColor() const {
    return vertColor_;
  }

  size_t getNum() const {
    return num_;
  }
};
