#include "Renderable.hpp"
#include "Texture.hpp"
#include "Wave.hpp"
class Flag : public Renderable {
private:
  const Texture &texture_;
  const Wave &wave_;
public:
  Flag(const Wave &wave, const Texture &texture);
  void render(ModelSetter ms, TextureSetter ts) const;
};
