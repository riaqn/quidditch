#include <vector>
#include <glm/glm.hpp>

#include "Noise.hpp"

class PerlinNoise : public Noise<float, glm::fvec2> {
  // The permutation vector
  std::vector<unsigned char> p;
public:
  PerlinNoise();
  PerlinNoise(unsigned int seed);
  float noise(const glm::fvec2 &u) const;
  float noise(const glm::fvec3 &u) const;
private:
  static glm::vec3 fade(const glm::vec3 &t) ;
  static float lerp(float t, float a, float b);
  float grad(const glm::uvec3 &t, const glm::fvec3 &v) const;
};
