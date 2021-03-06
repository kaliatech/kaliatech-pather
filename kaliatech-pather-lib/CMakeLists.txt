cmake_minimum_required(VERSION 3.0)
project(kaliatech-pather-lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp") # Define PROJECT_SOURCES as a list of all source files
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include/") # Define PROJECT_INCLUDE to be the path to the include directory of the project

set(sources ${PROJECT_SOURCE})
add_library(${PROJECT_NAME}  ${sources} ${includes})

# ---- glm
include(${CMAKE_DIR}/LinkGLM.cmake)
LinkGLM(kaliatech-pather-lib PUBLIC)
# ----

# ---- nlohmann_json
include(FetchContent)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_PROGRESS TRUE
        GIT_SHALLOW TRUE
        GIT_TAG v3.10.5)
FetchContent_MakeAvailable(json)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PRIVATE ${json_SOURCE_DIR}/single_include)
# ----



set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_INCLUDE}
      CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

option(BUILD_DOC "Build documentation" OFF)
find_package(Doxygen)
if (DOXYGEN_FOUND AND BUILD_DOC)
    set( DOXYGEN_OUTPUT_DIRECTORY docs/doxygen )
    doxygen_add_docs(docs
            "${CMAKE_CURRENT_SOURCE_DIR}/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/src"
            ALL
            COMMENT "Generate HTML documentation")

elseif (BUILD_DOC)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND AND BUILD_DOC)