#include "Bezier.hpp"
#include <map>

float Bezier::B(const unsigned n, const unsigned i, const float u) {
  static std::map<std::pair<unsigned, unsigned>, unsigned> cache;
  unsigned long long C;
  auto iter = cache.find(std::make_pair(n, i));
  if (iter == cache.end()) {
    C = 1;
    for (unsigned j = 1; j <= n; ++j)
      C *= j;
    for (unsigned j = 1; j <= i; ++j)
      C /= j;
    for (unsigned j = 1; j <= n - i; ++j)
      C /= j;
    cache.insert(std::make_pair(std::make_pair(n, i), C));
  } else {
    C = iter->second;
  }
  float ans = C;
  for (unsigned j = 0; j < i; ++j)
    ans *= u;
  for (unsigned j = 0; j < n - i; ++j)
    ans *= (1 - u);
  return ans;
}

Bezier::Bezier(const unsigned n, const unsigned m, const std::vector<glm::fvec2> &uv) 
  :n_(n), m_(m), b_(uv.size(), std::vector<std::vector<float> >(n + 1, std::vector<float>(m + 1))) {
  size_t N = uv.size();
  for (unsigned k = 0; k < N; ++k) {
    float u = uv[k].x;
    float v = uv[k].y;
    for (unsigned i = 0; i <= n; ++i)
      for (unsigned j = 0; j <= m; ++j)
        b_[k][i][j] = B(n, i, u) * B(m, j, v);
  }
}

float Bezier::get(const unsigned k) {
  float ans = 0;
  for (auto i = 0; i <= n_; ++i)
    for (auto j = 0; j <= m_; ++j)
      ans += b_[k][i][j] * (*k_)[i][j];
  return ans;
}

void Bezier::set(const std::vector<std::vector<float> > *const k) {
  k_ = k;
}
