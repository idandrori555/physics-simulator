# PhysicsSimulator

A 2D classical physics simulator with real-time SDL3 visualization, written in modern C++ (C++23). Built as a learning tool for understanding numerical integration, force dynamics, energy conservation, and collision response in discrete-time simulation.

## Features

- **2D vector math** — Full arithmetic, dot product, polar construction
- **Trapezoidal integration** — Second-order accurate average-velocity scheme
- **Forces & friction** — Add arbitrary forces with optional stop conditions; built-in friction and gravity helpers
- **Energy tracking** — Kinetic, potential, and total energy printed per tick
- **Singleton simulator** — Global state with ground plane collision and bounce
- **Conditional forces** — Per-frame force evaluation with automatic removal on stop
- **SDL3 graphical visualisation** — Real-time windowed rendering with velocity (green) and force (red) vector overlays
- **10 built-in scenarios** — Accessible via command-line argument

## Examples

Run any scenario by passing its number:

```bash
./.build/physics_sim <N>
```

| # | Description |
|---|-------------|
| 1 | Constant horizontal acceleration (rocket propulsion) |
| 2 | Sliding block with kinetic friction (braking) |
| 3 | Classical projectile motion (high parabolic arc) |
| 4 | Terminal velocity free-fall (high altitude drop) |
| 5 | Galileo drop experiment (mass independence in vacuum) |
| 6 | Artillery crossfire (angle optimisation mechanics) |
| 7 | Constant headwind drag (dynamic balancing forces) |
| 8 | Multi-stage fountain (simultaneous multi-angle projection) |
| 9 | Uniform circular motion (orbital mechanics) |
| 10 | Bouncing ball (bounce-back) |

## Build

Requires **CMake 3.25+** and a **C++23** compiler. SDL3 is fetched automatically from GitHub via `FetchContent`.

```bash
cmake -B build -S .
cmake --build build
```

## Run

```bash
./build/physics_sim <scenario_number>
```

A window opens showing the simulation. Object position, velocity, acceleration, and energy are logged to stdout each tick. Close the window to end the simulation.

## Project Structure

```
├── CMakeLists.txt
├── include/
│   ├── const.hpp         # Physical constants (timestep, gravity, screen dimensions)
│   ├── types.hpp         # Type aliases (mass_t, force_t, lambda_t, etc.)
│   ├── vector.hpp        # 2D vector struct
│   ├── object.hpp        # Object class (mass, forces, energy)
│   ├── simulator.hpp     # Simulator singleton
│   └── graphics.hpp      # SDL3 rendering engine
└── src/
    ├── main.cpp          # Entry point, 10 example scenarios
    ├── vector.cpp
    ├── object.cpp
    ├── simulator.cpp     # Simulation loop, time integration, ground collision
    └── graphics.cpp      # SDL3 window, event loop, vector/object rendering
```

## Notes

- The integration timestep doubles as the wall-clock frame delay — tweak `consts::time_step` for faster/slower playback.
- Ground collision inverts vertical velocity (perfectly elastic bounce).

## License

MIT
