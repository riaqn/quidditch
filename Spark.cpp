#include "Spark.hpp"
#include "utils.hpp"
#include <glm/gtc/random.hpp>
#include "Log.hpp"

void Spark::add(const btVector3 &pos,
                const float velocity) {
  btVector3 localInertia;
  btTransform tf(btTransform(quaternion_, pos));
  auto v = convert<btVector3>(glm::ballRand(velocity));
  
  if (off_ < group_.size()) {
    auto rb = group_[off_];
    rb->setWorldTransform(tf);
    rb->setLinearVelocity(v);
    vertColor_[off_] = color_;
  } else {
    btMotionState *ms = new btDefaultMotionState(tf);
    btRigidBody *rb = new btRigidBody(mass_, ms, shape_, localInertia_);
    rb->setLinearVelocity(v);
    group_.push_back(rb);
    vertColor_.push_back(color_);
    world_->add(rb, filter_, ~filter_);
  }
  ++off_;
  if (off_ == num_)
    off_ = 0;
}

bool Spark::control(const float elapsed) {
  for (auto &color : vertColor_) {
    color.w -= color_.w / lifetime_ * elapsed;
  }
}
