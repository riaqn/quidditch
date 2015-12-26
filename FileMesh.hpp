#pragma  once

#include <vector>
#include <string>
#include <BulletCollision/CollisionShapes/btStridingMeshInterface.h>
#include <LinearMath/btVector3.h>
#include <glm/glm.hpp>

class FileMesh : public btStridingMeshInterface {
  struct Subpart {
    std::vector<glm::fvec3> v;
    std::vector<glm::ivec3> t;
  };
  std::vector<Subpart> subparts_;
  mutable btVector3 aabbMin_, aabbMax_;
  mutable int hasAabb_;
public:
  FileMesh(std::istream &is);

  virtual void getLockedVertexIndexBase(unsigned char **vertexbase, int& numverts,PHY_ScalarType& type, int& stride,unsigned char **indexbase,int & indexstride,int& numfaces,PHY_ScalarType& indicestype,int subpart=0) {
    *vertexbase = NULL;
    *indexbase = NULL;
  }

  virtual void getLockedReadOnlyVertexIndexBase(const unsigned char **vertexbase, int& numverts,PHY_ScalarType& type, int& stride,const unsigned char **indexbase,int & indexstride,int& numfaces,PHY_ScalarType& indicestype,int subpart=0) const {
    const Subpart &sp = subparts_[subpart];
    *vertexbase = (unsigned char *)&sp.v[0][0];
    numverts = sp.v.size();
    type = PHY_FLOAT;
    stride = sizeof(glm::fvec3);

    *indexbase = (unsigned char *)&sp.t[0][0];
    indexstride = sizeof(glm::ivec3);
    numfaces = sp.t.size();
    indicestype = PHY_INTEGER;
  }

  /*
  virtual void getLockedReadOnlyCoordinateBase(const unsigned char **coordbase, int &numcoords, PHY_ScalarType &type, int &stride, int subpart = 0) const {
    
  }*/

  virtual int getNumSubParts() const { 
    return (int)subparts_.size();
  }

  virtual void	unLockVertexBase(int subpart) {(void)subpart;}

  virtual void	unLockReadOnlyVertexBase(int subpart) const {(void)subpart;}

  virtual void	preallocateVertices(int numverts){(void) numverts;}
  virtual void	preallocateIndices(int numindices){(void) numindices;}

  virtual bool	hasPremadeAabb() const;
  virtual void	setPremadeAabb(const btVector3& aabbMin, const btVector3& aabbMax ) const;
  virtual void	getPremadeAabb(btVector3* aabbMin, btVector3* aabbMax ) const;

};
