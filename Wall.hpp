#include "SingleController.hpp"

class Wall : public SingleController {
public:
  Wall(const SingleController &sc)
    :SingleController(sc) {}
};
