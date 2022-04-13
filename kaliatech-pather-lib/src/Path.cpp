#include "kaliatech-pather-lib/Path.h"

#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "kaliatech-pather-lib/utils/LineUtils.h"

namespace kpath {
    Path::Path(std::string id, const glm::vec2 &A, const glm::vec2 &B) :
            id(std::move(id)), A(A), B(B), type(PathType::LINE) {

    }

    Path::Path(std::string id, const glm::vec2 &A, const glm::vec2 &B, const glm::vec2 &center, float arcRadius) :
            id(std::move(id)), A(A), B(B), type(PathType::ARC), center(center), arcRadius(arcRadius) {

    }


    std::string Path::toString() const {
        std::ostringstream str;
        //str << "id:" + id + ",A:" << glm::to_string(A) << ",B:" << glm::to_string(B);
        str << "A:" << glm::to_string(A) << ",B:" << glm::to_string(B);
        return str.str();
    }

    glm::mat2x4 Path::AB() const {
        return LineUtils::asMatrix(A, B);
    }

    float Path::AngleA() const {
        vec2 p1 = vec2(center.x + arcRadius, center.y);
        vec2 p2 = vec2(A.x, A.y);
        return std::atan2(p2.y - p1.y, p2.x - p1.x);
//    vec2 UP = vec2(center.x, center.y);
//    float dot = UP.x*A.x + UP.y*A.y;      // dot product between [x1, y1] and [x2, y2]
//    float det = UP.x*A.y - UP.y*A.x;      // determinant
//    float angle = std::atan2(det, dot);  // atan2(y, x) or atan2(sin, cos)
//    return angle;
//    vec2 UP = vec2(0, 1);
//    return glm::angle(UP, glm::normalize(A));
    }

    float Path::AngleB() const {
        vec2 p1 = vec2(center.x + arcRadius, center.y);
        vec2 p2 = vec2(B.x, B.y);
        return std::atan2(p2.y - p1.y, p2.x - p1.x);

//    vec2 UP = vec2(center.x, center.y);
//    float dot = UP.x*B.x + UP.y*B.y;      // dot product between [x1, y1] and [x2, y2]
//    float det = UP.x*B.y - UP.y*B.x;      // determinant
//    float angle = std::atan2(det, dot);  // atan2(y, x) or atan2(sin, cos)
//    return angle;
//    vec2 UP = vec2(0, 1);
//    return glm::angle(UP, glm::normalize(B));
    }

    float Path::Angle() const {
        float dot = A.x * B.x + A.y * B.y;      // dot product between [x1, y1] and [x2, y2]
        float det = A.x * B.y - A.y * B.x;      // determinant
        float angle = std::atan2(det, dot);  // atan2(y, x) or atan2(sin, cos)
        return angle;

//    vec2 A = glm::normalize(A);
//    vec2 B = glm::normalize(B);
//    return glm::angle(A, B);
    }


    float Path::length() const {
        if (type == PathType::ARC) {
            return std::abs(arcRadius * Angle());
        }
        return std::abs(std::sqrt(pow(B.x - A.x, 2.0f) + pow(B.y - A.y, 2.0f)));
    }


}