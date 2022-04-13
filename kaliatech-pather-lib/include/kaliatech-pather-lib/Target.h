#ifndef KALIATECH_PATHER_LIB_TARGET_H
#define KALIATECH_PATHER_LIB_TARGET_H

#include "utils/Circle.h"
namespace kpath {
    class Target : public Circle {
    public:
        Target(float x, float y, float r);

        ~Target() override = default;
    };
}

#endif //KALIATECH_PATHER_LIB_TARGET_H
