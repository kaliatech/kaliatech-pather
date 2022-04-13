cmake_minimum_required(VERSION 3.16)
project(kaliatech-pather-lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(./kaliatech-pather-lib kaliatech-pather-lib)
add_subdirectory(./kaliatech-pather-lib-tests kaliatech-pather-lib-tests)
add_subdirectory(./kaliatech-pather-app-console kaliatech-pather-app-console)
add_subdirectory(./kaliatech-pather-app-gui kaliatech-pather-app-gui)


