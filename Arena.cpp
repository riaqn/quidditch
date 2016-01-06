#include "Arena.hpp"

void Arena::step(const float elapsed) {
  for (auto it = controllers_.begin(); it != controllers_.end(); ++it) {
    auto con = *it;
    if (con->control(elapsed, remove_)) {
      delete con;
    }
  }
  world_.stepSimulation(elapsed);
}
