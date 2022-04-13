cmake_minimum_required(VERSION 3.0)
project(kaliatech-pather-lib-tests CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp") # Define PROJECT_SOURCES as a list of all source files
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include/") # Define PROJECT_INCLUDE to be the path to the include directory of the project

# Declaring our executable
add_executable(${PROJECT_NAME} src/TestSuiteRunner.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
        ${PROJECT_INCLUDE}
        ${kaliatech-pather-lib_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
        kaliatech-pather-lib
        )

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/assets/test-map-1.json ${PROJECT_BINARY_DIR}/. )

add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_CURRENT_SOURCE_DIR}/assets
                        ${CMAKE_CURRENT_BINARY_DIR}/assets)