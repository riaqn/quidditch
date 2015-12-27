#include "Importer.hpp"
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
#include "utils.hpp"
#include "Log.hpp"
#include "FileMesh.hpp"


using namespace std;
using namespace boost::filesystem;

Importer::ParseException::ParseException()
  :runtime_error("")
{}


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
  btScalar friction, rollingFriction;
  is >> mass >> friction >> rollingFriction >> collisionShape >> userPointer;
  checkStream(is);
  btMotionState *ms = loadMotionState(is);
  btTransform tf;
  ms->getWorldTransform(tf);

  btVector3 localInertia(0, 0, 0);
  btCollisionShape *shape = loadCollisionShape(p.parent_path() / collisionShape);
  if (mass != 0)
    shape->calculateLocalInertia(mass, localInertia);
  btRigidBody::btRigidBodyConstructionInfo info(mass, ms, shape, localInertia);
  info.m_friction = friction;
  info.m_rollingFriction = rollingFriction;
  
  btRigidBody *rb = new btRigidBody(info);
                            
  if (userPointer == "NULL")
    rb->setUserPointer(NULL);
  else 
    rb->setUserPointer(upcb_((p.parent_path() / userPointer).string()));
  checkStream(is);
  return rb;
}


btMotionState *Importer::loadMotionState(std::istream &is) {
  btTransform tf(loadTransform(is));
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
  } else if (type == "TriangleMesh") {
    return loadTriangleMeshShape(is);
  } else if (type == "Box") {
    return loadBoxShape(is);
  } else
    throw ParseException();
}

btSphereShape *Importer::loadSphereShape(std::istream &is) {
  btScalar radius ;
  is >> radius;
  checkStream(is);
  return new btSphereShape(radius);
}

btTriangleMeshShape *Importer::loadTriangleMeshShape(std::istream &is) {
  FileMesh *fm = new FileMesh(is);
  return new btBvhTriangleMeshShape(fm, true);
}

btBoxShape *Importer::loadBoxShape(std::istream &is) {
  btVector3 vec;
  is >> vec;
  checkStream(is);
  return new btBoxShape(vec);
}
