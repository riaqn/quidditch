#include "SingleController.hpp"
class Ground : public SingleController {
public:
  Ground(const SingleController &sc)
    :SingleController(sc) {}
};
