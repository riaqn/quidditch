#include "Arena.hpp"
#include "Log.hpp"

void Arena::step(const float elapsed) {
  auto it = controllers_.begin(); 
  while (it != controllers_.end()) {
    auto con = *it;
    if (con->control(elapsed)) {
      it = controllers_.erase(it);
      delete con;
    } else
      ++it;
  }
  world_.stepSimulation(elapsed);

  /*
  const btCollisionObjectArray &array = world_.getCollisionObjectArray();
  for (auto i = 0; i < array.size(); ++i) {
    auto rb = static_cast<btRigidBody *>(array.at(i));
    debug << rb << '\t' << rb->getWorldTransform().getOrigin() << '\n';
    }*/
}
