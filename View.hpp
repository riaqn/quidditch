#include <glm/glm.hpp>

class View {
public:
  View(glm::vec3 &&eye, glm::vec3 &&center, glm::vec3 &&up);
  glm::mat4 matrix() const ;
private:
  glm::vec3 eye_, center_, up_;
};
