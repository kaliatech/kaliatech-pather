#ifndef KALIATECH_PATHER_LIB_UTILS_LINEUTILS_H
#define KALIATECH_PATHER_LIB_UTILS_LINEUTILS_H

#include "glm/glm.hpp"

using glm::vec2;

namespace kpath {

/**
 * Utility class for line operations.
 */
    class LineUtils {
    public:
        /**
         * Convert two 2D vectors to a 2x4 matrix.
         *
         * @param A
         * @param B
         *
         * @return
         */
        static glm::mat2x4 asMatrix(const vec2 &A, const vec2 &B) {
            glm::mat2x4 CF = glm::mat2x4();
            CF[0].x = A.x;
            CF[0].y = A.y;
            CF[0].z = 1;
            CF[1].x = B.x;
            CF[1].y = B.y;
            CF[1].z = 1;
            return CF;
        }
    };

}
#endif //KPATH_APP_RAYLIB_LINEUTILS_H
