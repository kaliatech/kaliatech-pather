
#include "kaliatech-pather-lib/PathSequence.h"
#include "kaliatech-pather-lib/Target.h"

namespace kpath {
    PathSequence::PathSequence() {}

    void PathSequence::addPath(std::shared_ptr<Path> path) {
        paths.emplace_back(path);
        accumulatedLength += path->length();
    }

    const std::vector<std::shared_ptr<Path>> &PathSequence::getPaths() const {
        return paths;
    }

    float PathSequence::getAccumulatedLength() const {
        return accumulatedLength;
    }

    float PathSequence::getHeuristic(const Target &target) const {
        glm::vec2 last = paths.back()->B;
        glm::vec2 goalVec = glm::vec2(target.x, target.y);
        return getAccumulatedLength() + glm::distance(last, goalVec);
    }
}