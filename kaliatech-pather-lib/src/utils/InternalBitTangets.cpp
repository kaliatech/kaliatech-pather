#include "kaliatech-pather-lib/utils/InternalBitTangets.h"

#include <glm/glm.hpp>

#include "kaliatech-pather-lib/utils/LineUtils.h"
#include "kaliatech-pather-lib/utils/Circle.h"

namespace kpath {
    InternalBitTangets::InternalBitTangets(const Circle &A, const Circle &B) :
            a{A},
            av{vec2(A.x, A.y)},
            b{B},
            bv{vec2(B.x, B.y)} {
    }

    glm::mat2x4 InternalBitTangets::CF() {
        return LineUtils::asMatrix(C(), F());
    }

    glm::mat2x4 InternalBitTangets::DE() {
        return LineUtils::asMatrix(D(), E());
    }

    bool InternalBitTangets::isValid() {
        float d = glm::distance(av, bv);
        return d > a.r + b.r;
        //return (a.r + b.r) / d > 1;
    }

}