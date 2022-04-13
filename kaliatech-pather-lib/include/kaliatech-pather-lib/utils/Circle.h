#ifndef KALIATECH_PATHER_LIB_UTILS_CIRCLE_H
#define KALIATECH_PATHER_LIB_UTILS_CIRCLE_H

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/string_cast.hpp"

using glm::vec2;

namespace kpath {

    class Circle {
    public:
        Circle(float x, float y, float r);

        virtual ~Circle() = default;

        std::string toString() {
            std::ostringstream str;
            str << "x:" << x << ",y:" << y << ",r:" << r;
            return str.str();
        }

        bool intersects(const glm::vec2 &A, const glm::vec2 &B) const {
            vec2 C = vec2(x, y);
            vec2 CA = C - A;
            vec2 BA = B - A;

            float u = glm::dot(CA, BA) / glm::dot(BA, BA);
            float cu = glm::clamp(u, 0.0f, 1.0f);

            vec2 E = A + (cu * (B - A));
            float d = std::abs(glm::distance(C, E));

//            std::cout << "C:" << glm::to_string(C) << std::endl;
//            std::cout << "A:" << glm::to_string(A) << std::endl;
//            std::cout << "B:" << glm::to_string(B) << std::endl;
//            std::cout << "u:" << u << std::endl;
//            std::cout << std::setprecision(10) << "d:" << (float)d << std::endl;
//            std::cout << std::setprecision(10) << "r:" << (float)r << std::endl;

            //TODO: expose this if precision matters
            const float EPSILON = .0001f;
            if (std::abs(d - r) < EPSILON) {
                return false;
            } else {
                return d < r;
            }
            //return false;
        }

        inline bool operator==(const Circle &other) const {
            return this->x == other.x && this->y == other.y && this->r == other.r;
        }

    public:
        float x;
        float y;
        float r;

    };
}

#endif //KALIATECH_PATHER_LIB_UTILS_CIRCLE_H
