#include "kaliatech-pather-lib/Map.h"

#include <utility>

namespace kpath {
    Map::Map(int width, int height, std::vector<Obstacle> obstacles)
            : width(width), height(height), obstacles(std::move(obstacles)) {

    }

    int Map::getWidth() const {
        return width;
    }

    int Map::getHeight() const {
        return height;
    }

    const std::vector<Obstacle> &Map::getObstacles() const {
        return obstacles;
    }
}