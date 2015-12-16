#include "Renderable.hpp"
#include "Texture.hpp"
#include "Wave.hpp"
class Flag : public Renderable {
private:
  const Texture &texture_;
  const Wave &wave_;
public:
  Flag(const Wave &wave, const Texture &texture);
  void render(const GLuint WVP, const glm::mat4 &VP) const;
};
