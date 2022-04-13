#include "kaliatech-pather-lib/utils/ExternalBitTangets.h"

#include <glm/glm.hpp>

#include "kaliatech-pather-lib/utils/LineUtils.h"
#include "kaliatech-pather-lib/utils/Circle.h"

namespace kpath {
    ExternalBitTangets::ExternalBitTangets(const Circle &A, const Circle &B) :
            a{A},
            av{vec2(A.x, A.y)},
            b{B},
            bv{vec2(B.x, B.y)} {
    }

    ExternalBitTangets::ExternalBitTangets(const Circle &A, const Circle &B,  float aRadiusInc, float bRadiusInc) :
            ExternalBitTangets(A, B) {
        a.r += aRadiusInc;
        b.r += bRadiusInc;
    }


    glm::mat2x4 ExternalBitTangets::CF() {
        return LineUtils::asMatrix(C(), F());
    }

    glm::mat2x4 ExternalBitTangets::DE() {
        return LineUtils::asMatrix(D(), E());
    }

    bool ExternalBitTangets::isValid() {
        float d = glm::distance(av, bv);
        //return std::abs((a.r - b.r / d) > 1);
        return d > a.r + b.r;
    }
}