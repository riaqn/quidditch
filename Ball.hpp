#include "Renderable.hpp"
#include <glm/glm.hpp>
#include <vector>

class Ball : public Renderable {
private:
  GLuint VBO_, IBO_;
  static void evolve(std::vector<glm::vec3> &v, std::vector<glm::uvec3> &i, const unsigned age);
  static void normalize(std::vector<glm::vec3> &v);
public:
  Ball();
  void render(const GLuint WVP, const glm::mat4 &VP);
};
