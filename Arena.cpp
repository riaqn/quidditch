#include "Arena.hpp"

void Arena::deduce(const float t) {
  for (auto i = balls_.begin(); i != balls_.end(); ++i) {
    Ball &b = **i;
    glm::vec3 v1 = b.v - b.m * g * mu * glm::normalize(b.v) * t;
    
    (*i)->pos += (b.v + v1) * t * 0.5f;
    b.v = v1;
  }

  //collision test
  for (auto i = balls_.begin(); i != balls_.end(); ++i)
    for (auto j = balls_.begin(); j != balls_.end(); ++j)
      if (i != j) {
        Ball &b0 = **i;
        Ball &b1 = **j;

        glm::vec3 dist = b0.pos - b1.pos;
        
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
