#ifndef KALIATECH_PATHER_LIB_POINT_H
#define KALIATECH_PATHER_LIB_POINT_H


#include <string>

namespace kpath {
    class Point {
    public:
        float x;
        float y;

        Point() = default;

        Point(float x, float y) : x(x), y(y) {};

        virtual ~Point() = default;

        std::string toString();

        inline bool operator==(const Point &other) const {
            return this->x == other.x && this->y == other.y;
        }
    };
}

#endif //KALIATECH_PATHER_LIB_POINT_H
