#include "BoxShape.hpp"
#include "utils.hpp"

void BoxShape::draw(ScaleSetter ss) const {
  ss(convert(shape_->getHalfExtentsWithMargin()));
  if (box_ == NULL)
    box_ = new Box();
  box_->draw();
}

const Box *BoxShape::box_ = NULL;
