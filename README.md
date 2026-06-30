# PhysicsSimulator

A minimal 2D classical physics simulator written in modern C++ (C++23). Built as a learning tool for understanding numerical integration, force dynamics, and energy conservation in discrete-time simulation.

## Features

- **2D vector math** — Full arithmetic, dot product, polar construction
- **Trapezoidal integration** — Second-order accurate average-velocity scheme (vs. naive Euler)
- **Forces & friction** — Add arbitrary forces with optional stop conditions; built-in friction helper
- **Energy tracking** — Kinetic, potential, and total energy printed per tick
- **Singleton simulator** — Simple global state, configurable tick count and timestep
- **Zero external dependencies** — Only the C++ standard library

## Examples

| # | Description |
|---|-------------|
| 1 | 1D motion under constant acceleration |
| 2 | 1D motion with friction (initial velocity + friction to stop) |

### Planned

| # | Description |
|---|-------------|
| 3 | 1D motion with gravity |
| 4 | 2D projectile throw |
| 5 | 2D circular motion |

## Build

Requires **CMake 3.25+** and a **C++23** compiler.

```bash
cmake -B .build -S .
cmake --build .build
```

## Run

```bash
./.build/physics_sim
```

Output is printed to stdout — one frame per tick with per-object position, velocity, acceleration, and energy.

## Project Structure

```
├── CMakeLists.txt
├── include/
│   ├── const.hpp         # Physical constants (timestep, gravity)
│   ├── object.hpp        # Object class (mass, forces, energy)
│   ├── simulator.hpp     # Simulator singleton
│   └── vector.hpp        # 2D vector struct
└── src/
    ├── main.cpp          # Entry point, example scenarios
    ├── object.cpp
    ├── simulator.cpp     # Simulation loop, time integration
    └── vector.cpp
```

## Notes

- The integration timestep doubles as the wall-clock frame delay — tweak `consts::time_step` for faster/slower playback.
- Friction is implemented via a stop-condition busy-wait (in progress).

## License

MIT
