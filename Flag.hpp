#include "Render.hpp"
#include "Texture.hpp"
#include "Wave.hpp"
class Flag : public Render {
private:
  const Texture &texture_;
  const Wave &wave_;
public:
  Flag(const Wave &wave, const Texture &texture);
  void render(ModelSetter ms, MaterialSetter ts) const;
};
