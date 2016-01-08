#include "SingleController.hpp"
class Ground : public SingleController {
public:
  Ground(SingleController &&sc)
    :SingleController(std::move(sc)) {}
};
