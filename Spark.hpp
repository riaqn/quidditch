#include "GroupController.hpp"

class Spark : public GroupController {
  btCollisionShape *shape_;
  const btQuaternion quaternion_;
  const btScalar mass_;
  const int filter_;
  
  btVector3 localInertia_;

  const size_t num_;
  const float lifetime_;
  size_t off_;

  std::vector<glm::vec4> vertColor_;

  const glm::vec4 color_;
public:
  Spark(const size_t num,
        const float lifetime,
        btCollisionShape *shape,
        const btQuaternion &quaternion,
        const btScalar mass,
        const int filter,
        const glm::vec4 color)
    :num_(num), lifetime_(lifetime), off_(0),
     shape_(shape), quaternion_(quaternion),
     mass_(mass), filter_(filter),
     color_(color) {
    shape->calculateLocalInertia(mass, localInertia_);
  }

  void add(const btVector3 &pos,
           const float radius);

  virtual bool control(const float elapsed);

  const std::vector<glm::vec4> &getVertColor() {
    return vertColor_;
  }
};
