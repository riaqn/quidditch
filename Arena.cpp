#include "Arena.hpp"
#include "GhostBall.hpp"
#include "WanderBall.hpp"
#include "Log.hpp"
#include <glm/gtc/random.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>

void Arena::deduce(const float t) {
  bool flag;
  unsigned time = 0;
  do {
    flag = true;
    ++time;
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
            b.v *= w.c;
            b.x += (b.r - dist) * glm::normalize(w.n);

            flag = false;
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
            debug << "collision " << i - balls_.begin() << "<->" << j - balls_.begin() << '\n';
            float &m0 = b0.m;
            float &m1 = b1.m;
            glm::vec3 &v0 = b0.v;
            glm::vec3 &v1 = b1.v;
            glm::vec3 &x0 = b0.x;
            glm::vec3 &x1 = b1.x;
            glm::vec3 v0_ = v0 - (2 * m1) / (m0 + m1) * glm::dot(v0 - v1, x0 - x1) / glm::dot(x0 - x1, x0 - x1) * (x0 - x1);
            glm::vec3 v1_ = v1 - (2 * m0) / (m0 + m1) * glm::dot(v1 - v0, x1 - x0) / glm::dot(x1 - x0, x1 - x0) * (x1 - x0);

            v0 = v0_;
            v1 = v1_;
            flag = false;
          }
        }
      }
  } while (!flag);
  if (time > 2)
    debug << "time = " << time << "\n";

  /*
  for (auto i = balls_.begin(); i != balls_.end(); ++i) {
    Ball &b = **i;
    debug << i - balls_.begin() << ' ' << b.x.x << ' ' << b.x.y << ' ' << b.x.z << '\n';
  }
  */

  
  for (auto i = balls_.begin(); i != balls_.end(); ++i) {
    if (auto b = dynamic_cast<GhostBall *>(*i)) {
      float v = glm::length(b->v);
      glm::vec3 v1 = b->v + g * t;
      b->x += (b->v + v1) * t * 0.5f;
      b->v = v1;
    } else if (auto b = dynamic_cast<WanderBall *>(*i)) {
      float v = glm::length(b->v);
      if (v == 0)
        b->v = glm::linearRand(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
      float v1f = v + (b->v0 - v) * b->mu * t;
      glm::vec3 v1 = glm::normalize(b->v) * v1f;
      v1 += g * t;

      b->x += (b->v + v1) * t / 2.0f;
      b->v = v1;
    } else {
      error << "strange ball!\n"; 
    }
  }

}

void Arena::attach(Ball *ball) {
  balls_.push_back(ball);
}

void Arena::attach(Wall *wall) {
  walls_.push_back(wall);
}
