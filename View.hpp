#include <glm/glm.hpp>

class View {
public:
  View(const glm::vec3 &eye, const glm::vec2 &angle);
  void up(const float d);
  void right(const float d);
  void turn(const glm::vec2 &d);
  glm::mat4 matrix() const ;
private:
  glm::vec3 eye_;
  glm::vec2 angle_;
  glm::vec3 direction_, right_, up_;
};
