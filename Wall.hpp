#include "SingleController.hpp"

class Wall : public SingleController {
public:
  Wall(SingleController &&sc)
    :SingleController(std::move(sc)) {}
};
