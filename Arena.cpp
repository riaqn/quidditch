#include "Arena.hpp"
#include "GhostBall.hpp"
#include "WanderBall.hpp"
#include "SnitchBall.hpp"
#include "CueBall.hpp"

#include "Log.hpp"
#include <glm/gtc/random.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Arena::deduce(const float t) {
  for (auto i = balls_.begin(); i != balls_.end(); ++i) {
    if (auto b = dynamic_cast<GhostBall *>(*i)) {
      if (onGround(b)) {
        b->v.y = 0;
        float v = glm::length(b->v);
        if (v > 0) {
          float v1 = v - glm::length(g) * mu * t;
          if (v1 < 0) v1 = 0;
          b->v *= v1 / v;
        }
      } else {
        b->v += g * t;
      }
    } else if (auto b = dynamic_cast<WanderBall *>(*i)) {
      if (onGround(b)) {
        debug << "Wanderball is on Ground\n";
        if (glm::length(b->v) == 0) {
          b->v = glm::linearRand(glm::vec3(-1, 0, -1), glm::vec3(1, 0, 1));
        }
        b->v.y = 0;
        glm::vec3 v1 = glm::normalize(glm::rotateY(b->v, glm::linearRand(-glm::pi<float>() / 2, glm::pi<float>() / 2))) * b->v0;
        b->v += (v1 - b->v) * b->mu * t;
      } else {
        debug << "Wanderball is on fly\n";
        b->v += g * t;
      }
    } else if (auto b = dynamic_cast<SnitchBall *>(*i))  {
      if (b->isSleep) {
        b->countdown -= t;
        if (b->countdown < 0) {
          debug << "Snatch timeout, going fly\n";
          b->isSleep = false;
          b->countdown = 10;
        }
        if (onGround(b)) {
          b->v.y = 0;
          float v = glm::length(b->v);
          if (v > 0) {
            float v1 = v - glm::length(g) * mu * t;
            if (v1 < 0) v1 = 0;
            b->v *= v1 / v;
          }
        } else {
          b->v += g * t;
        }
      } else {
        b->countdown -= t;
        if (b->countdown < 0) {
          debug << "Snatch timeout, going sleep\n";
          b->isSleep = true;
          b->countdown = 10;
        }
        glm::vec3 dst = glm::linearRand(b->zone_min, b->zone_max);
        glm::vec3 v =  glm::normalize(dst - b->x) * b->v0;
        b->v += (v - b->v) * mu * t;
      }
    } else {
      error << "strange ball!\n"; 
    }
    Ball &b = **i;
  }

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
            b.v *= w.c ;
            /*b.x += (b.r - dist) * glm::normalize(w.n);*/

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
            for (int t = 0; t < 2; ++t) {
              
              if (SnitchBall *b = dynamic_cast<SnitchBall *>(*i))
                if (onGround(b))
                  if (dynamic_cast<CueBall *>(*j)) {
                    b->isSleep = false;
                    b->countdown = 10;
                  }
              if (dynamic_cast<CueBall *>(*i)) {
                if (dynamic_cast<GhostBall *>(*j))
                  score += 1;
                else if (dynamic_cast<WanderBall *>(*j))
                  score += 2;
                else if (dynamic_cast<SnitchBall *>(*j))
                  score += 3;
              }
              swap(i, j);
            }
          }
        }
      }
  } while (!flag);
  if (time > 2)
    debug << "time = " << time << "\n";


  for (auto i = balls_.begin(); i != balls_.end(); ++i) {
    Ball &b = **i;
    debug << i - balls_.begin() << '\t' << glm::to_string(b.x) << '\t' << glm::to_string(b.v) << '\n';
  }

  for (auto i = balls_.begin(); i != balls_.end(); ++i) {
    Ball &b = **i;
    b.x += b.v * t;
  }
}

void Arena::attach(Ball *ball) {
  balls_.push_back(ball);
}

void Arena::attach(Wall *wall) {
  walls_.push_back(wall);
}

bool Arena::onGround(const Ball *ball) const {
  debug << ball->x.y << " " << ball->r << '\n';
  if ((glm::abs(ball->x.y - ball->r) < 0.01) &&
      (glm::abs(ball->v.y) < 0.01))
    return true;
  else
    return false;
    
}
