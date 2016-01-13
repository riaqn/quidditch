#pragma once
#include "Controller.hpp"
#include <BulletSoftBody/btSoftBodyHelpers.h>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "PerlinNoise.hpp"

class Cloth : public Controller {
  std::unique_ptr<btSoftBody> sb_;
  PerlinNoise noise_;
  float ts_;
public:
  Cloth(Cloth &&cloth)
    :sb_(std::move(cloth.sb_)),
     ts_(0) {
    sb_->setUserPointer(this);
  }

  static void getRectangle(const unsigned nx,
                           const unsigned ny,
                           std::vector<glm::vec2> &nodes,
                           std::vector<glm::ivec3> &faces);
  
  Cloth(btSoftBodyWorldInfo &worldinfo,
        const std::vector<glm::vec2> &nodes,
        const std::vector<glm::ivec3> &faces,
        const glm::vec3 &base,
        const glm::vec3 &x,
        const glm::vec3 &y);

  btSoftBody &getBody() {
    return *sb_;
  }

  int getNode(const unsigned x, const unsigned y) {
    
  }
  
  virtual void init(WorldProxy &world) {
    world.add(sb_.get());
  }

  virtual bool control(const float elapsed);
};
