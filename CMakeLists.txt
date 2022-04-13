cmake_minimum_required(VERSION 3.0)
project(kaliatech-pather-lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(./kaliatech-pather-lib kaliatech-pather-lib)
add_subdirectory(./kaliatech-pather-app-console kaliatech-pather-app-console)
add_subdirectory(./kaliatech-pather-app-gui kaliatech-pather-app-gui)