#pragma once
#include "SingleController.hpp"

class Ball : public SingleController {
public:
  Ball(const btRigidBody::btRigidBodyConstructionInfo &info)
    :SingleController(info) {}
};
