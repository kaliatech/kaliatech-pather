#ifndef KALIATECH_PATHER_LIB_PATHSEQUENCE_H
#define KALIATECH_PATHER_LIB_PATHSEQUENCE_H

#include <vector>
#include <memory>

#include "PathSequence.h"
#include "Path.h"
#include "Target.h"
#include "Types.h"
namespace kpath {
    class PathSequence {
    public:
        PathSequence();

        void addPath(std::shared_ptr<Path> path);

        const PathVector &getPaths() const;

        float getAccumulatedLength() const;

        float getHeuristic(const Target &goal) const;


    private:
        PathVector paths;
        float accumulatedLength = 0;
    };
}

#endif // KALIATECH_PATHER_LIB_PATHSEQUENCE_H
