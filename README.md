# kaliatech-pather

A C++ library for 2D path finding a sphere through spherical obstacles.

Many concepts in this library are explained further by Amit Patel in his article:
 - [Circular Obstacle Pathfinding](https://redblobgames.github.io/circular-obstacle-pathfinding/)

## Components
 * **kaliatech-pather-lib**
   * A static C++ library. Only dependency is GLW (and that will eventually be removed.)
 * **kaliatech-pather-lib-tests**
   * Executable unit tests.
 * **kaliatech-pather-app-console**
   * A console app for feeding a map file to the library and getting optimal path.
* **kaliatech-pather-app-gui**
    * A GUI app for displaying map and optimal path.

## Building and Executing
All code is cross platform C++20. Tested:
 * Windows 10 using MSVC compiler and CLion IDE.
 * Ubuntu 20.04 (on WSL2, no GUI)
 * Amazon Linux 2

### Install dependencies

```bash
sudo apt install cmake build-essential git
```
Additional dependencies might be needed for the GUI app.
```bash
# In a Windows WSL2 environment with Ubuntu 20.04
sudo apt install cmake build-essential git
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
```
### Clone, Build, Execute
```bash
# Clone
git clone https://github.com/kaliatech/kaliatech-pather.git

# Run cmake
cd kaliatech-panther
cmake -S . -B build

# Run make
cd ./build
make

# Execute the console app
cd ./kaliatech-pather-console-app
./kaliatech-pather-console-app assets/test-map-1.json
```

## Status (2020-04-13)

Priorities:
 - The path finding neighbor look-up has a bug and can go in to an infinite loop.
 - Does not yet handle concept of seeker having it's own size.

Remaining work:
 - Refactoring to remove dependency on GLW from the static library (uses vec2 types)
 - Refactoring the graph building
 - Refactoring to allow plugable algorithms
 - Optimization, especially in the graph building
 - Testing, especially:
   - limits testing (memory usage, out-of-bounds, number overruns, etc.)
   - performance measurements


