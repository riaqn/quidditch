#include "GroupController.hpp"
#include <random>
#include <functional>
#include "Noise.hpp"

class Smoke : public Controller {
public:
  typedef std::function<glm::vec4 ()> GenerateCallback; 
private:
  GenerateCallback cb_;
  const size_t num_;
  size_t off_;
  const float rate_;
  const float k_;

  float ts_;
  const glm::vec4 &color_;

  std::vector<glm::vec4> vertOffset_;
  std::vector<glm::vec4> vertColor_;

  const Noise<float, glm::vec3> &noise_;
public:

  Smoke(const GenerateCallback cb,
        const size_t num,
        const float rate,
        const glm::vec4 &color,
        const Noise<float, glm::vec3> &noise)
    :cb_(cb), num_(num), off_(0), rate_(rate), color_(color), ts_(0), noise_(noise),k_(glm::pow(0.01, rate / num)) {}
  
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
