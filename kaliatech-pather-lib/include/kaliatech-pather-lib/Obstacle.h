#ifndef KALIATECH_PATHER_LIB_OBSTACLE_H
#define KALIATECH_PATHER_LIB_OBSTACLE_H

#include <string>
#include <functional>

#include "utils/Circle.h"
#include "Point.h"

namespace kpath {
/**
 * A circular obstacle.
 */
    class Obstacle : public Circle {
    public:
        Obstacle(std::string id, float x, float y, float r);

        ~Obstacle() override = default;

        const std::string &getId() const;

    private:
        /**
         * Must be unique for all objects on map.
         */
        std::string id;
    };


}

namespace std {
    template<>
    struct hash<kpath::Obstacle> {
        std::size_t operator()(const kpath::Obstacle &obstacle) const noexcept {
            return std::hash<std::string>()(obstacle.getId());
        }
    };
}
#endif //KPATH_APP_OBSTACLE_H
