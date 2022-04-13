#ifndef KALIATECH_PATHER_LIB_KPATHPLANNER_H
#define KALIATECH_PATHER_LIB_KPATHPLANNER_H

#include <string>
#include <memory>

#include <unordered_map>
#include "Path.h"

#include "Map.h"
#include "Point.h"

#include "Seeker.h"
#include "PathSequence.h"
#include "Target.h"
#include "Types.h"

namespace kpath {

    /**
     * Main class to use kpath library.
     */
    class PathFinder {
    public:
        PathFinder() = default;
        virtual ~PathFinder() = default;

        PathSequence find(const Map& map, const Seeker& seeker, const Target& target);

    private:
        void buildGraph(const Map &map, const Seeker &seeker, const Target &target);

        void addSeekerPaths(const std::string& idBase, const Seeker& seeker, const Obstacle &B);
        void addTargetPaths(const std::string& idBase, const Obstacle& A, const Target &target);
        void addObstaclePaths(const std::string& idBase, const Obstacle& A, Obstacle &B);

        PathSequence a_star_search(const Target& target);
        PathVector getNextNeighbors(const std::shared_ptr<Path>& lastPath);

    public:
        const PathVector & getSeekerPaths() const;
        const ObstaclePathMap& getStartObjPaths() const;

        const PathVector & getArcPaths() const;


    private:
        PathVector startSeekerPaths;

        ObstaclePathMap startObjPaths;
        ObstaclePathMap endObjPaths;

        PathVector arcPaths;
    };
}

#endif // KALIATECH_PATHER_LIB_KPATHPLANNER_H
