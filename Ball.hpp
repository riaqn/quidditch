#pragma once
#include "SingleController.hpp"

class Ball : public SingleController {
public:
  Ball(SingleController &&ball)
    :SingleController(std::move(ball)) {}

};
