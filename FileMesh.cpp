#include "FileMesh.hpp"
#include <istream>

#include "utils.hpp"

using namespace std;

FileMesh::FileMesh(istream &is) {
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

bool	FileMesh::hasPremadeAabb() const
{
	return (hasAabb_ == 1);
}


void	FileMesh::setPremadeAabb(const btVector3& aabbMin, const btVector3& aabbMax ) const
{
	aabbMin_ = aabbMin;
	aabbMax_ = aabbMax;
	hasAabb_ = 1; // this is intentionally an int see notes in header
}

void	FileMesh::getPremadeAabb(btVector3* aabbMin, btVector3* aabbMax ) const
{
	*aabbMin = aabbMin_;
	*aabbMax = aabbMax_;
}

