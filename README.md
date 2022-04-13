# kaliatech-pather

A C++ library for 2D path finding a circle through circular obstacles. Many concepts in this library are explained
further by Amit Patel in his article:

- [Circular Obstacle Pathfinding](https://redblobgames.github.io/circular-obstacle-pathfinding/) - Amit Patel / Red Blob
  Games

## Components

* **kaliatech-pather-lib**
    * A static C++ library. Only dependency is GLW (and that will eventually be removed.)
      <br><br>
* **kaliatech-pather-lib-tests**
    * Executable unit tests.
      <br><br>
* **kaliatech-pather-app-console**
    * A console app for feeding a map file to the library and getting optimal path.
      <br><br>
* **kaliatech-pather-app-gui**
    * A GUI app for displaying map and optimal path.

## Building and Executing

Code is cross platform in C++20. Tested:

* Windows 10, using MSVC 2019 compiler and CLion IDE.
* Ubuntu 20.04 (with WSL2)
* Amazon Linux 2

### Install dependencies

The kaliatech-path-library itself has only one non standard library dependency (GLW), and that can/should/will be
removed. The GUI app requires additional dependencies on linux.

Minimum requirements to clone source and build:

* **CMake 3.16+**
* **C++20 compiler**
* **Git**
* **Git LFS**

#### Windows

Works easily in newer versions of CLion. It _should_ also work with MSVC, but I did not test.

#### Linux

A number of additional dependencies are needed on linux, mostly for the GUI app due to it's use
of [raylib](https://www.raylib.com/).

```bash
# Basics
sudo apt install cmake build-essential git git-lfs
```

```bash
# In a Windows WSL2 environment with Ubuntu 20.04
sudo apt install cmake build-essential git
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
```

```bash
# In Amazon Linux 2 (where available gcc and cmake are too old)

sudo yum install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel

sudo yum remove gcc.x86_64
sudo yum install -y gcc10.x86_64 gcc10-c++.x86_64
sudo ln -s /usr/bin/gcc10-gcc /usr/bin/gcc
sudo ln -s /usr/bin/gcc10-g++ /usr/bin/g++

sudo yum remove cmake #if installed
sudo yum install openssl-devel #required by newer versions of cmake
sudo yum install -y 
wget https://cmake.org/files/v3.16/cmake-3.16.3.tar.gz
tar -xvzf cmake-3.16.3.tar.gz
cd cmake-3.16.3
./bootstrap
gmake
sudo gmake install
```

### Clone, Build, Execute

```bash
# Clone
git clone https://github.com/kaliatech/kaliatech-pather.git

# Run cmake
cd kaliatech-pather
cmake -S . -B build

# Run make
cd ./build
make

# Execute the console app
cd ./kaliatech-pather-app-console
./kaliatech-pather-app-console assets/test-map-1.json

# Execute the GUI app
cd ./kaliatech-pather-app-gui
./kaliatech-pather-app-gui assets/test-map-1.json

# Workaround for Amazon Linux 2
MESA_GL_VERSION_OVERRIDE=4.3 ./kaliatech-pather-app-gui assets/test-map-1.json
```

## Status (2020-04-13)

Remaining priorities:

- The path finding neighbor look-up has a bug and can go in to an infinite loop.
- The path finding arc calculations are not correct.
- The GUI display does not draw arcs. It currently uses orange lines where there should be curves.

Potential tasks:

- Refactoring to remove dependency on GLW from the static library (uses vec2 types)
- Refactoring the graph building
- Refactoring to allow pluggable search algorithms
- Optimizations, especially in the graph building
- Testing, especially:
    - limits testing (memory usage, out-of-bounds, number overruns, etc.)
    - performance measurements



