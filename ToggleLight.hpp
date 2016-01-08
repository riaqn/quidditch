#include "Light.hpp"

class ToggleLight : public Light {
  const Light &light_;
  bool switch_;
public:
  ToggleLight(const Light &light)
    :light_(light),
     switch_(true) {}

  bool toggle() {
    return switch_ = !switch_;
  }
  
  virtual Spec operator() () const {
    Spec spec = light_();
    if (!switch_)
      spec.intensities = glm::vec3(0);
    return spec;
  }
};
