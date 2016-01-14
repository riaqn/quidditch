#include "Cloth.hpp"
#include "Log.hpp"
#include <stdexcept>


void Cloth::getRectangle(const unsigned nx,
                         const unsigned ny,
                         std::vector<glm::vec2> &nodes,
                         std::vector<glm::ivec3> &faces) {
  for (auto i = 0; i <= nx; ++i)
    for (auto j = 0; j <= ny; ++j) {
      nodes.push_back(glm::vec2((float)i / nx, (float)j / ny));
    }
  auto idx = [&ny](const int i, const int j) {
    return i * (ny + 1) + j;
  };
  for (auto i = 0; i < nx; ++i)
    for (auto j = 0; j < ny; ++j) {
      faces.push_back(glm::ivec3(idx(i, j), idx(i+1, j), idx(i, j+1)));
      faces.push_back(glm::ivec3(idx(i, j+1), idx(i+1, j), idx(i+1, j+1)));
    }
}

Cloth::Cloth(btSoftBodyWorldInfo &worldinfo,
             const std::vector<glm::vec2> &nodes,
             const std::vector<glm::ivec3> &faces,
             const glm::vec3 &base,
             const glm::vec3 &x,
             const glm::vec3 &y) {
  std::vector<glm::vec3> nodes0;
  for (auto &node : nodes)
    nodes0.push_back(base + node.x * x + node.y * y);
  sb_ = std::unique_ptr<btSoftBody>(btSoftBodyHelpers::CreateFromTriMesh(worldinfo, &nodes0[0].x, &faces[0].x, faces.size()));
  sb_->setUserPointer(this);
  btSoftBody::Config &c = sb_->m_cfg;
  /*
  c.kDP = 0.0;// Damping coefficient [0,1]
  c.kDG = 0;
  c.kLF = 0;
  c.kPR = 0;
  c.kVC = 0;
  c.kDF = 0.2;// Dynamic friction coefficient [0,1]
  c.kMT = 0.01;// Pose matching coefficient [0,1]
  */
  c.kCHR = 1.0;// Rigid contacts hardness [0,1]
  c.kKHR = 0.8;// Kinetic contacts hardness [0,1]
  c.kSHR = 1.0;// Soft contacts hardness [0,1]
  c.kAHR = 1.0;
  /*
  c.piterations=2;
  sb_->m_materials[0]->m_kLST = 0.8;
  sb_->m_materials[0]->m_kAST = 0.8;
  sb_->m_materials[0]->m_kVST = 0.8;
  sb_->scale(btVector3(1,1,1));
  //        sb_->setPose(true, true);
  */
  //sb_->generateBendingConstraints(2);
  //sb_->randomizeConstraints();

  //c.collisions =  btSoftBody::fCollision::CL_SS+
  //btSoftBody::fCollision::CL_RS;
  //sb_->generateClusters(1);
  /*
  sb_->m_clusters[0]->m_matching	=	0.01;
  sb_->m_clusters[0]->m_ndamping	=	0.01;
  */
  sb_->setTotalMass(0.01,true);
  sb_->setPose(false,true);
}

bool Cloth::control(const float elapsed) {
  ts_ += elapsed;
  auto &nodes(sb_->m_nodes);
  for (auto i = 0; i < nodes.size(); ++i) {
    auto &node(nodes[i].m_x);
    btVector3 v(noise_.noise(glm::vec3(ts_ / 4, node.y(), node.z()) / 64.0f),
                noise_.noise(glm::vec3(node.x(), ts_ / 4, node.z()) / 64.0f),
                noise_.noise(glm::vec3(node.x(), node.y(), ts_ / 4) / 64.0f));
    float n = v.length();
    //debug << n << '\n';
    if (glm::isnan(n) || n < 0 || n > 2)
      continue;
    
    //sb_->addAeroForceToNode(v * 500, i);
    sb_->addForce(v / 2000, i);
    //    debug << v << '\n';
  }
  
  return false;
}
