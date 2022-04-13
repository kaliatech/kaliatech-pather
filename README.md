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
Install dependencies.

Minimally **cmake 3.0+**, a **C++20 compiler**, Git and Git LFS.

GUI requires additional dependencies on linux.

On Windows, a git clone works out-of-the-box in newer versions of CLion. It _should_ also
work on MSVC, but I did not test.

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

Priorities:
 - The path finding neighbor look-up has a bug and can go in to an infinite loop.
 - The path finding arc calculations are not correct.
 - The GUI display does not draw arcs. It currently uses orange lines where there should be curves.

Remaining work:
 - Refactoring to remove dependency on GLW from the static library (uses vec2 types)
 - Refactoring the graph building
 - Refactoring to allow plugable algorithms
 - Optimization, especially in the graph building
 - Testing, especially:
   - limits testing (memory usage, out-of-bounds, number overruns, etc.)
   - performance measurements


