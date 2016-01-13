#include "Noise.hpp"
#include "SimpleMesh.hpp"
#include <limits>

class NoiseGround : public SimpleMesh {
private:
  //const Noise<float, glm::vec2> &noise_;
public:
  NoiseGround(const Noise<float, glm::vec2> &noise,
              const glm::vec3 &base,
              const glm::vec3 &x,
              const glm::vec3 &y,
              const unsigned nx,
              const unsigned ny,
              const float height)
    :SimpleMesh(1) {
    Subpart &sp = subparts_.back();
    
    glm::vec3 h = glm::normalize( glm::cross(x, y)) * height;

    float max = std::numeric_limits<float>::max();
    aabbMin_.setValue(max, max, max);
    aabbMax_.setValue(-max, -max, -max);
    
    for (auto i = 0; i <= nx; ++i)
      for (auto j = 0; j <= ny; ++j) {
        float px = (float)i / nx;
        float py = (float)j / ny;
        sp.v.push_back(base + px * x + py * y + h * noise.noise(glm::vec2(px, py) / 50.0f));
        glm::vec3 &v = sp.v.back();
        for (auto k = 0; k < 3; ++k) {
          if (v[k] < aabbMin_.m_floats[k])
            aabbMin_.m_floats[k] = v[k];
          else if (v[k] > aabbMax_.m_floats[k])
            aabbMax_.m_floats[k] = v[k];
        }          

      }
    hasAabb_ = true;

    debug << aabbMin_ << '\n';
    debug << aabbMax_ << '\n';
    
    
    auto idx = [&ny](const int i, const int j) {
      return i * (ny + 1) + j;
    };

    for (auto i = 0; i < nx; ++i)
      for (auto j = 0; j < ny; ++j) {
        sp.t.push_back(glm::ivec3(idx(i, j), idx(i+1, j), idx(i, j+1)));
        sp.t.push_back(glm::ivec3(idx(i, j+1), idx(i+1, j), idx(i+1, j+1)));
      }
  }
};
