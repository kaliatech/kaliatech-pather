#ifndef KPATH_PATH_PATH_H
#define KPATH_PATH_PATH_H

#include "glm/glm.hpp"

#include <string>

#include "Obstacle.h"
#include "Point.h"
#include "Seeker.h"

namespace kpath {
    enum PathType {
        LINE, ARC
    };

    class Path {
    public:
        Path(std::string id, const glm::vec2 &A, const glm::vec2 &B);

        Path(std::string id, const glm::vec2 &A, const glm::vec2 &B, const glm::vec2 &center, float arcRadius);

        std::string id;
        glm::vec2 A;
        glm::vec2 B;
        PathType type;

        glm::vec2 center;
        float arcRadius = 0;

        glm::mat2x4 AB() const;

        float AngleA() const;

        float AngleB() const;

        float Angle() const;

        float length() const;

        std::string toString() const;

        inline bool operator==(const Path &other) const {
            return this->id == other.id;

//        return this->id == other.id &&
//               this->A == other.A &&
//               this->B == other.B &&
//               this->type == other.type &&
//               this->arcRadius == other.arcRadius;
        }
    };

}
#endif //KPATH_APP_PATH_H
