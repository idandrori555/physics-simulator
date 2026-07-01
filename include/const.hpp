#pragma once

#include "types.hpp"

struct consts
{
  inline static const double time_step = .016; // 60fps ish
  inline static const gravity_t gravity = 10;
  inline static const int SCREEN_WIDTH = 1600;
  inline static const int SCREEN_HEIGHT = 1200;
  inline static const double METERS_TO_PIXELS = 20.0;
};
