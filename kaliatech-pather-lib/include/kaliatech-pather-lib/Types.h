#ifndef KALIATECH_PATHER_LIB_TYPES_H
#define KALIATECH_PATHER_LIB_TYPES_H

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Obstacle.h"
#include "Path.h"
namespace kpath {
    typedef std::unordered_map<Obstacle, std::vector<std::shared_ptr<Path>>> ObstaclePathMap;

    typedef std::vector<std::shared_ptr<Path>> PathVector;
}
#endif