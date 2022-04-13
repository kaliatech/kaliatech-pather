#ifndef KALIATECH_PATHER_LIB_SEEKER_H
#define KALIATECH_PATHER_LIB_SEEKER_H

#include "utils/Circle.h"
namespace kpath {
    class Seeker : public Circle {
    public:
        Seeker(float x, float y, float r);

        ~Seeker() override = default;
    };
}
#endif //KPATH_APP_SEEKER_H
