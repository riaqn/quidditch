#include <btBulletDynamicsCommon.h>
#include "Scene.hpp"

class World {
  btDynamicsWorld &world_;
  Scene &scene_;
public:
  World(btDynamicsWorld &world, Scene &scene)
    :world_(world), scene_(scene) {}
};
