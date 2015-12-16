#include <vector>
#include <glm/glm.hpp>

class Bezier {
  
public:
  Bezier(const unsigned n, const unsigned m, const std::vector<glm::fvec2> &uv);
  float get(const unsigned k);
  void set(const std::vector<std::vector<float> > *const k);
private:
  float B(const unsigned n, const unsigned i, const float u);
  unsigned n_, m_;
  std::vector<std::vector<std::vector<float> > > b_;
  const std::vector<std::vector<float> > *k_;
};
