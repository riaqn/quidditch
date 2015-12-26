#include <btBulletDynamicsCommon.h>
#include <string>
#include <boost/filesystem.hpp>
#include <functional>
#include <exception>

class Importer {
public:
  class ParseException : public std::runtime_error {
  public:
    ParseException();
  };
  typedef std::function<void (const btRigidBody * const)> Callback;
  typedef std::function<void *(const std::string &)> UserPointerCallback;
private:
  btDiscreteDynamicsWorld *dynamicsWorld_;
  UserPointerCallback upcb_;
  static void checkStream(const std::istream &is);
public:
  
  Importer(btDiscreteDynamicsWorld *const dynamicsWorld,
           UserPointerCallback upcb);
  void loadWorld(const boost::filesystem::path &path, Callback cb);
  btRigidBody *loadRigidBody(const boost::filesystem::path &path);
  void *loadUserPointer(const boost::filesystem::path &path);
  btMotionState *loadMotionState(std::istream &is);
  btCollisionShape *loadCollisionShape(const boost::filesystem::path &path);
  btSphereShape *loadSphereShape(std::istream &is);
  btTriangleMeshShape *loadTriangleMeshShape(std::istream &is);
  btTriangleIndexVertexArray *loadTriangleIndexVertexArray(std::istream &is);
  btTransform loadTransform(std::istream &is);
};
