#include "Importer.hpp"
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
#include "utils.hpp"

#include "Log.hpp"


using namespace std;
using namespace boost::filesystem;

Importer::ParseException::ParseException()
  :runtime_error("")
{}

istream &operator>>(istream &is, btVector3 &vec) {
  btScalar s;
  is >> s;
  vec.setX(s);
  is >> s;
  vec.setY(s);
  is >> s;
  vec.setZ(s);
  return is;
}

ostream &operator<<(ostream &os, const btVector3 &vec) {
  os << '[' << vec.x()
     << ',' << vec.y()
     << ',' << vec.z()
     << ']';
  return os;
}

void Importer::checkStream(const std::istream &is) {
  if (!is.good())
    throw ParseException();
}

Importer::Importer(btDiscreteDynamicsWorld *const dynamicsWorld,
                   UserPointerCallback upcb)
  :dynamicsWorld_(dynamicsWorld), upcb_(upcb) {}

void Importer::loadWorld(const path &p, Callback cb) {
  ifstream is(p.string());
  btVector3 gravity;
  is >> gravity;
  checkStream(is);
              
  dynamicsWorld_->setGravity(gravity);
  path rigidBody;
  while (is >> rigidBody) {
    btRigidBody *rb = loadRigidBody(p.parent_path() / rigidBody);
    dynamicsWorld_->addRigidBody(rb);
    cb(rb);
  }
}

btRigidBody *Importer::loadRigidBody(const path &p) {
  notice << "loadRigidBody():" << p << '\n';
  ifstream is(p.string());
  btScalar mass;
  path collisionShape;
  path userPointer;
  is >> mass >> collisionShape >> userPointer;
  checkStream(is);
  btMotionState *ms = loadMotionState(is);
  btTransform tf;
  ms->getWorldTransform(tf);
  debug << "fuck" << tf.getOrigin() << '\n';
  btRigidBody *rb = new btRigidBody(mass,
                                    ms,
                                    loadCollisionShape(p.parent_path() / collisionShape));
  rb->setUserPointer(upcb_((p.parent_path() / userPointer).string()));
  checkStream(is);
  return rb;
}


btMotionState *Importer::loadMotionState(std::istream &is) {
  btTransform tf(loadTransform(is));
  debug << "fuck2" << tf.getOrigin() << '\n';
  return new btDefaultMotionState(tf);
}

btTransform Importer::loadTransform(std::istream &is) {
  btScalar x, y, z;
  is >> x >> y >> z;
  checkStream(is);
  btTransform tf(btQuaternion(0, 0, 0, 1), btVector3(x, y, z));
  debug << "tf.getOrigin() = " << tf.getOrigin() << '\n';
  return tf;
}

btCollisionShape *Importer::loadCollisionShape(const path &p) {
  notice << "loadCollisionShape(): " << p << '\n';
  ifstream is(p.string());
  path type;
  is >> type;
  checkStream(is);
  if (type == "Sphere") {
    return loadSphereShape(is);
  } 
}

btSphereShape *Importer::loadSphereShape(std::istream &is) {
  btScalar radius ;
  is >> radius;
  checkStream(is);
  return new btSphereShape(radius);
}
