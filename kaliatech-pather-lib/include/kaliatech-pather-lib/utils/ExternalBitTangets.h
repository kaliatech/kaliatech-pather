#ifndef KALIATECH_PATHER_LIB_UTILS_ExternalBITANGETS_H
#define KALIATECH_PATHER_LIB_UTILS_ExternalBITANGETS_H

#include <vector>
#include <glm/glm.hpp>

#include "Circle.h"

using glm::vec2;

namespace kpath {

    /**
     * Class for finding external bitangents between two circles, if any.
     * @see https://redblobgames.github.io/circular-obstacle-pathfinding/*
     */
    class ExternalBitTangets {
    public:
        ExternalBitTangets(const Circle &A, const Circle &B);

        float theta() {
            const float P = glm::distance(av, bv);
            const float cos_angle = (a.r - b.r) / P;
            return std::acos(cos_angle);
        }

        float AB_angle() { return vec_facing(av, bv); }

        vec2 C() { return direction_step(av, a.r, AB_angle() - theta()); }

        vec2 D() { return direction_step(av, a.r, AB_angle() + theta()); }

        vec2 E() { return direction_step(bv, b.r, AB_angle() + theta()); }

        vec2 F() { return direction_step(bv, b.r, AB_angle() - theta()); }

        glm::mat2x4 CF();

        glm::mat2x4 DE();

        bool isValid();

    private:
        float vec_facing(vec2 p, vec2 q) {
            float dx = q.x - p.x;
            float dy = q.y - p.y;
            return std::atan2(dy, dx);
        };

        vec2 direction_step(vec2 start, float distance, float angle) {
            return start + vec_polar(distance, angle);
        };

        vec2 vec_polar(float d, float a) {
            return vec2(d * std::cos(a), d * std::sin(a));
        };

    private:
        Circle a;
        vec2 av;
        Circle b;
        vec2 bv;

    };

}
#endif //KALIATECH_PATHER_LIB_UTILS_ExternalBITANGETS_H
