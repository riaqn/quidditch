#include "Light.hpp"

class SimpleLight : public Light {
  const Spec &spec_;
public:
  SimpleLight(const Spec &spec)
    :spec_(spec) { }

  virtual Spec operator() () const {
    return spec_;
  }
};
