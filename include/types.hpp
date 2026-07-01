#pragma once

#include <functional>

struct Vector;
struct Object;

using energy_t = double;
using mass_t = double;
using position_t = Vector;
using velocity_t = Vector;
using acceleration_t = Vector;
using force_t = Vector;
using friction_t = double;
using gravity_t = double;
using lambda_t = std::function<bool(Object &)>;
