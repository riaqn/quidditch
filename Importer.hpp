#include <string>
#include <boost/filesystem.hpp>
#include <functional>
#include <exception>
#include "Arena.hpp"

class Importer {
public:
  class ParseException : public std::runtime_error {
  public:
    ParseException();
  };
  typedef std::function<void (Controller *const, std::istream &)> CustomDataCallback;
private:
  static void checkStream(const std::istream &is);
  Arena &arena_;
public:
  Importer(Arena &arena)
    :arena_(arena) {}
  
  void loadArena(const boost::filesystem::path &path, CustomDataCallback cb);
  btRigidBody::btRigidBodyConstructionInfo loadRigidBody(const boost::filesystem::path &path);
  btMotionState *loadMotionState(std::istream &is);
  btCollisionShape *loadCollisionShape(const boost::filesystem::path &path);
  btSphereShape *loadSphereShape(std::istream &is);
  btTriangleMeshShape *loadNoiseGround(std::istream &is);
  btTriangleMeshShape *loadTriangleMeshShape(std::istream &is);
  btBoxShape *loadBoxShape(std::istream &is);
  btTriangleIndexVertexArray *loadTriangleIndexVertexArray(std::istream &is);
  btTransform loadTransform(std::istream &is);
};
