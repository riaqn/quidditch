#include "Importer.hpp"
#include <fstream>
#include <sstream>
#include <memory>
#include <boost/filesystem.hpp>
#include "utils.hpp"
#include "Log.hpp"
#include "FileMesh.hpp"
#include "NoiseGround.hpp"

#include "GhostBall.hpp"
#include "WanderBall.hpp"
#include "SnitchBall.hpp"
#include "CueBall.hpp"
#include "FantasyBall.hpp"

#include "Ground.hpp"
#include "Wall.hpp"

#include "PerlinNoise.hpp"



using namespace std;
using namespace boost::filesystem;

Importer::ParseException::ParseException()
  :runtime_error("")
{}


void Importer::checkStream(const std::istream &is) {
  if (!is.good())
    throw ParseException();
}

void Importer::loadArena(const path &p, CustomDataCallback cb) {
  ifstream is(p.string());
  while (is) {

    stringstream ss;
    string line;
    while (std::getline(is, line)) {
      if (line.size() == 0)
        break;
      ss << line << ' ';
    }
    if (ss.str().size() == 0)
      continue;

    string type;
    ss >> type;
    path rb;
    ss >> rb;
    btRigidBody::btRigidBodyConstructionInfo info = loadRigidBody(p.parent_path() / rb);
    Controller *con;
    if (type == "GhostBall") {
      con = new GhostBall(Ball(info));
    } else if (type == "WanderBall") {
      float v0, mu;
      ss >> v0 >> mu;
      con = new WanderBall(Ball(info), v0, mu);
    } else if (type == "CueBall") {
      float p, f;
      ss >> p >> f;
      con = new CueBall(Ball(info), p, f);
    } else if (type == "SnitchBall") {
      float t0, t1;
      btVector3 min, max, mu;
      float v0;
      ss >> t0 >> t1 >> min >> max >> mu >> v0;
      con = new SnitchBall(Ball(info), t0, t1, min, max, mu, v0);
    } else if (type == "FantacyBall") {
      float duration;
      ss >> duration;
      con = new FantasyBall(Ball(info), duration);
    } else if (type == "Ground") {
      con = new Ground(info);
    } else if (type == "Wall") {
      con = new Wall(info);
    } else 
      throw std::runtime_error("");
    arena_.add(con);
    cb(con, ss);
  }
}

btRigidBody::btRigidBodyConstructionInfo Importer::loadRigidBody(const path &p) {
  notice << "loadRigidBody():" << p << '\n';
  ifstream is(p.string());
  btScalar mass;
  path collisionShape;
  btScalar friction, rollingFriction;
  is >> mass >> friction >> rollingFriction >> collisionShape;
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

  checkStream(is);
  return info;
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
  } else if (type == "NoiseGround") {
    return loadNoiseGround(is);
  } else
    throw ParseException();
}

btSphereShape *Importer::loadSphereShape(std::istream &is) {
  btScalar radius ;
  is >> radius;
  checkStream(is);
  return new btSphereShape(radius);
}

btTriangleMeshShape *Importer::loadNoiseGround(std::istream &is) {
  glm::vec3 base, x, y;
  unsigned nx, ny;
  float height;
  is >> base >> x >> y >> nx >> ny >> height;

  PerlinNoise noise;
  auto *ng = new NoiseGround(noise, base, x, y, nx, ny, height);
  return new btBvhTriangleMeshShape(ng, true);
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
