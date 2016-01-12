#include "FileMesh.hpp"
#include "utils.hpp"

using namespace std;

FileMesh::FileMesh(istream &is)
  :SimpleMesh(0) { 
  unsigned nsp;
  is >> nsp;
  for (auto k = 0; k < nsp; ++k) {
    subparts_.push_back(Subpart{});
    Subpart &sp = subparts_.back();
    unsigned n, m;
    is >> n >> m;
    for (auto i = 0; i < n; ++i) {
      glm::fvec3 v;
      is >> v;
      sp.v.push_back(v);
    }
    for (auto i = 0; i < m; ++i) {
      glm::ivec3 t;
      is >> t;
      sp.t.push_back(t);
    }
  }
}
