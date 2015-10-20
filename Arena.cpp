#include "Arena.hpp"
#include "GhostBall.hpp"
#include "WanderBall.hpp"
#include "Log.hpp"
#include <glm/gtc/random.hpp>
#include <glm/gtc/quaternion.hpp>

void Arena::deduce(const float t) {
  for (auto i = balls_.begin(); i != balls_.end(); ++i) {
    if (auto b = dynamic_cast<GhostBall *>(*i)) {
      glm::vec3 v1 = b->v - b->m * g * mu * glm::normalize(b->v) * t;
      b->x += (b->v + v1) * t * 0.5f;
      b->v = v1;
    } else if (auto b = dynamic_cast<WanderBall *>(*i)) {
      float v = glm::length(b->v);
      if (v == 0)
        b->v = glm::linearRand(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
      float v1f = v + (b->v0 - v) * b->mu * t;
      glm::vec3 v1 = glm::normalize(b->v) * v1f;
      b->x += (b->v + v1) * t * 0.5f;
      b->v = v1;
    } else {
      error << "strange ball!\n"; 
    }
  }

  //bound check
  for (auto i = balls_.begin(); i != balls_.end(); ++i)
    for (auto j = walls_.begin(); j != walls_.end(); ++j) {
      Ball &b = **i;
      Wall &w = **j;
      float dist = (glm::dot(b.x, w.n) + w.d) / glm::length(w.n);
      if (dist < b.r) {
        float tendency = glm::dot(b.v, w.n);
        if (tendency < 0) {
          float l = glm::length(w.n);
          glm::vec3 proj = tendency / (l * l) * w.n;
          b.v -= proj * 2.0f;
        }
      }
    }
  
  //collision test
  for (auto i = balls_.begin(); i != balls_.end(); ++i)
    for (auto j = i + 1; j != balls_.end(); ++j) {
      Ball &b0 = **i;
      Ball &b1 = **j;

      glm::vec3 dist = b0.x - b1.x;

      if (glm::length(dist) < b0.r + b1.r) {
        float tendency = glm::dot(b0.v, dist) - glm::dot(b1.v, dist);
        if (tendency < 0) {
          std::swap(b0.v, b1.v);
        }
      }
    }
}

void Arena::attach(Ball *ball) {
  balls_.push_back(ball);
}

void Arena::attach(Wall *wall) {
  walls_.push_back(wall);
}
