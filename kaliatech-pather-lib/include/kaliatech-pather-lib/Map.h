#ifndef KALIATECH_PATHER_LIB_MAP_H
#define KALIATECH_PATHER_LIB_MAP_H

#include <vector>

#include "Obstacle.h"

namespace kpath {

    /**
     * An rectangular map with obstacles.
     */
    class Map {
    public:
        /**
         *
         * @param width total width of map
         * @param height total height of map
         * @param obstacles obstacles on the map. Will be copied.
         */
        Map(int width, int height, std::vector<Obstacle> obstacles);

        virtual ~Map() = default;
        int getWidth() const;
        int getHeight() const;

        const std::vector<Obstacle> &getObstacles() const;


    private:
        int width;
        int height;
        const std::vector<Obstacle> obstacles;
    };
}

#endif //KPATH_APP_MAP_H
