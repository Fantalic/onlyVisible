# onlyVisible

> **onlyVisible** — screen-space occlusion culling terrain demo in C++ + raylib.

`onlyVisible` procedurally generates a 400×400 Perlin-noise terrain (160,000 cubes) and renders only the cubes that project onto the screen. The visible cubes fade in as they enter the viewport, and a live HUD shows the current visible count. Built as a learning project for **visibility culling techniques** — the foundation of efficient rendering in large worlds.

## Project Structure

```
├── src/
│   ├── main.cpp             # Entry point: terrain generation + render loop
│   ├── Cube.cpp             # Cube class with screen-space culling logic
│   └── PerlinNoise.cpp      # Improved Perlin noise (Ken Perlin reference impl.)
├── include/
│   ├── Cube.h               # Cube declaration, CUBE_SIZE, vertex/face data
│   ├── PerlinNoise.h        # Perlin noise declaration (seeded permutation vec)
│   └── rlgl.h               # Vendored raylib rlgl header v5.0 (OpenGL abstraction)
├── CMakeLists.txt           # C++17, FetchContent → raylib 5.5
├── run.sh                   # Cross-platform configure + build + launch
├── install.sh               # System dependency installer (Linux X11/GL, macOS)
├── AGENTS.md                # Developer notes
└── .gitignore
```

## Architecture — Screen-Space Culling

The core technique is deliberately simple: for each cube, project its 3D position to 2D screen coordinates via `GetWorldToScreen()`. If the result falls outside `[0, width] × [0, height]`, the cube is hidden. No spatial index, no frustum planes — just a brute-force projection check.

```
Camera → GetWorldToScreen(pos) → (x, y) on screen?
  ├── Yes → draw cube with fade-in alpha ramp (+10/frame)
  └── No  → skip (culled)
```

- **Coarse culling**: works at cube level, checks only the center point
- **160K cube world**: without culling, rendering all cubes per frame would be prohibitive
- **Fade-in**: smooth alpha ramp when cubes enter the viewport
- **Planned spatial grid**: a commented-out design in `main.cpp` describes an octree-style 3D grid for future work

## Quick Start

**No manual raylib installation required** — CMake's `FetchContent` downloads raylib 5.5 source automatically.

### Prerequisites

- **C++17 compiler** (GCC, Clang, MSVC)
- **CMake 3.20+**
- **Git** (for FetchContent to download raylib)

Platform-specific setup:

| Platform | Compiler | System deps |
|----------|----------|-------------|
| **Linux** | GCC / Clang | `./install.sh` (X11, GL) |
| **macOS** | Apple Clang | `./install.sh` (Homebrew → raylib) |
| **Windows (MinGW)** | GCC (w64devkit, MSYS2) | None — bundled with toolchain |
| **Windows (WSL)** | GCC in WSL | `./install.sh` inside WSL |

### Build & Run

```bash
# One command — configure, build, launch
./run.sh
```

Or manually:

```bash
# Linux / macOS / WSL
cmake -B build -S .
cmake --build build
./build/Game

# Windows (MinGW / Git Bash)
cmake -B build -S . -G "MinGW Makefiles"
cmake --build build
./build/Game.exe
```

The `run.sh` script auto-detects your platform and uses the correct generator and binary name.

## Technologies

- **C++17** — Modern C++ standard
- **raylib 5.5** — Graphics, windowing, input, math (via CMake FetchContent)
- **Perlin Noise** — Ken Perlin's "Improved Perlin" reference implementation (Java → C++)
- **CMake** — Build system with FetchContent for automatic dependency management
