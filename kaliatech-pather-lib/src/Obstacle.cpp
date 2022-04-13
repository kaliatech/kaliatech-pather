#include "kaliatech-pather-lib/Obstacle.h"
#include "kaliatech-pather-lib/utils/Circle.h"

namespace kpath {
    Obstacle::Obstacle(std::string id, float x, float y, float r) : Circle(x, y, r), id(std::move(id)) {

    }

    const std::string &Obstacle::getId() const {
        return id;
    }
}