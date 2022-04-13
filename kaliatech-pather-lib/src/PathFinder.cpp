#include <string>
#include <queue>
#include <vector>

#include <glm/glm.hpp>

#include "kaliatech-pather-lib/Map.h"
#include "kaliatech-pather-lib/Obstacle.h"
#include "kaliatech-pather-lib/PathFinder.h"
#include "kaliatech-pather-lib/PathSequence.h"
#include "kaliatech-pather-lib/Seeker.h"
#include "kaliatech-pather-lib/Target.h"
#include "kaliatech-pather-lib/Types.h"
#include "kaliatech-pather-lib/utils/ExternalBitTangets.h"
#include "kaliatech-pather-lib/utils/InternalBitTangets.h"

namespace kpath {

    PathSequence PathFinder::find(const Map &map, const Seeker &seeker, const Target &target) {
        buildGraph(map, seeker, target);
        return a_star_search(target);
    }

    void PathFinder::addSeekerPaths(const std::string &idBase, const Seeker &seeker, const Obstacle &B) {

        auto &endObjPathsV = endObjPaths[B];

        Circle seekerC(seeker.x, seeker.y, 0);

        ExternalBitTangets ebt(seekerC, B);
        if (ebt.isValid()) {
            std::shared_ptr<Path> p1(new Path(idBase + "-ebt1", ebt.C(), ebt.F()));
            startSeekerPaths.emplace_back(p1);
            endObjPathsV.emplace_back(p1);

            std::shared_ptr<Path> p2(new Path(idBase + "-ebt2", ebt.D(), ebt.E()));
            startSeekerPaths.emplace_back(p2);
            endObjPathsV.emplace_back(p2);
        }
    }

    void PathFinder::addTargetPaths(const std::string &idBase, const Obstacle &A, const Target &target) {
        auto &startObjPathsV = startObjPaths[A];

        Circle targetC(target.x, target.y, 0);
        ExternalBitTangets ebt(A, targetC);
        if (ebt.isValid()) {
            std::shared_ptr<Path> p1(new Path(idBase + "-ebt1", ebt.C(), ebt.F()));
            startObjPathsV.emplace_back(p1);

            std::shared_ptr<Path> p2(new Path(idBase + "-ebt2", ebt.D(), ebt.E()));
            startObjPathsV.emplace_back(p2);
        }
    }

    void PathFinder::addObstaclePaths(const std::string &idBase, const Obstacle &A, Obstacle &B) {
        auto &startObjPathsV = startObjPaths[A];
        auto &endObjPathsV = endObjPaths[B];

        ExternalBitTangets ebt(A, B);
        if (ebt.isValid()) {
            std::shared_ptr<Path> p1(new Path(idBase + "-ebt1", ebt.C(), ebt.F()));
            startObjPathsV.emplace_back(p1);
            endObjPathsV.emplace_back(p1);

            std::shared_ptr<Path> p2(new Path(idBase + "-ebt2", ebt.D(), ebt.E()));
            startObjPathsV.emplace_back(p2);
            endObjPathsV.emplace_back(p2);
        }

        InternalBitTangets ibt(A, B);
        if (ibt.isValid()) {
            auto p1 = std::make_shared<Path>(Path(idBase + "-ibt1", ibt.C(), ibt.F()));
            startObjPathsV.emplace_back(p1);
            endObjPathsV.emplace_back(p1);

            std::shared_ptr<Path> p2(new Path(idBase + "-ibt2", ibt.D(), ibt.E()));
            startObjPathsV.emplace_back(p2);
            endObjPathsV.emplace_back(p2);
        }
    }

    void PathFinder::buildGraph(const Map &map, const Seeker &seeker, const Target &target) {
        startSeekerPaths.clear();
        startObjPaths.clear();
        endObjPaths.clear();
        arcPaths.clear();

        // Seeker directly to target
        glm::vec2 seekerNode = vec2(seeker.x, seeker.y);
        glm::vec2 targetNode = vec2(target.x, target.y);
        std::shared_ptr<Path> seekerToTarget(new Path("seekerToTarget", seekerNode, targetNode));
        startSeekerPaths.emplace_back(seekerToTarget);

        // Iterate through all Obstacles
        for (Obstacle o: map.getObstacles()) {
            // Create maps to cache starts and ends
            startObjPaths[o] = std::vector<std::shared_ptr<Path>>();
            std::vector<std::shared_ptr<Path>> &startObjPathsV = startObjPaths[o];

            // Seeker path to every obstacle bittangent
            addSeekerPaths("seekerTo-" + o.getId(), seeker, o);

            // Every obstacle bittangent to target
            addTargetPaths(o.getId() + "-toTarget", o, target);

            // Every obstacle bittangent with every obstacle bittangent
            for (Obstacle o2: map.getObstacles()) {
                if (o == o2) {
                    continue;
                }
                if (!endObjPaths.contains(o2)) { //Todo: more efficient way to do this
                    endObjPaths[o2] = std::vector<std::shared_ptr<Path>>();
                }
                std::vector<std::shared_ptr<Path>> &endObjPathsV = endObjPaths[o2];

                addObstaclePaths("obj-" + o.getId() + "-to-" + o2.getId(), o, o2);
            }
        }

        // Remove all intersections
        for (Obstacle mapObstacles: map.getObstacles()) {
            // Remove intersections from seeker initiated paths
            startSeekerPaths.erase(std::remove_if(startSeekerPaths.begin(),
                                                  startSeekerPaths.end(),
                                                  [&](const std::shared_ptr<Path> p) -> bool {
                                                      return mapObstacles.intersects(p->A, p->B);
                                                  }),
                                   startSeekerPaths.end());

            // Remove intersections from all obstacle initiated paths
            for (auto &[currObstacle, paths]: startObjPaths) {
                if (mapObstacles.getId() == currObstacle.getId()) {
                    continue;
                }

                paths.erase(std::remove_if(paths.begin(),
                                           paths.end(),
                                           [&](const std::shared_ptr<Path> p) -> bool {
                                               return mapObstacles.intersects(p->A, p->B);
                                           }),
                            paths.end());
            }
        }


        for (const auto &obstacle: map.getObstacles()) {
            auto &startArcAtBPaths = endObjPaths[obstacle];
            for (const auto &startArcAtBPath: endObjPaths[obstacle]) {
                auto &endArcAtAPaths = startObjPaths[obstacle];
                for (const auto &endArcAtAPath: endArcAtAPaths) {
                    //TODO:self obstacle check
                    std::shared_ptr<Path> arcPath(
                            new Path("arc-" + obstacle.getId() + "-" + startArcAtBPath->toString() + "-" + endArcAtAPath->toString(),
                                     startArcAtBPath->B,
                                     endArcAtAPath->A,
                                     vec2{obstacle.x, obstacle.y},
                                     obstacle.r)
                    );
                    arcPaths.emplace_back(arcPath);
                }
            }
        }
    }

    //TODO:
    class CompareFunc {
    public:
        const Target &target;

        CompareFunc(const Target &target) : target(target) {}

        bool operator()(const PathSequence &a, const PathSequence &b) {
            return a.getHeuristic(target) > b.getHeuristic(target);
        }
    };

    PathSequence PathFinder::a_star_search(const Target &target) {

        vec2 targetVec = vec2(target.x, target.y);

//        auto compare = [t](const PathSequence& a, const PathSequence& b) {
//            //return a.getAccumulatedLength() < b.getAccumulatedLength();
//            return a.getHeuristic(t) < b.getHeuristic(t);
//        };
//        std::priority_queue<PathSequence, std::vector<PathSequence>, decltype(compare)> pathSequenceQueue;

        auto compFunc = CompareFunc(target);
        std::priority_queue<PathSequence, std::vector<PathSequence>, CompareFunc> pathSequenceQueue(compFunc);

        for (std::shared_ptr<Path> p: startSeekerPaths) {
            PathSequence pSeq;
            pSeq.addPath(p);
            pathSequenceQueue.push(pSeq);
        }


        while (!pathSequenceQueue.empty()) {
            PathSequence topPathSeq = pathSequenceQueue.top();
            pathSequenceQueue.pop();

            std::shared_ptr<Path> lastPath = topPathSeq.getPaths().back();
            if (lastPath->B == targetVec) {
                return topPathSeq;
            }
//            std::cout << lastPath->toString() << ",cost:" << topPathSeq.getAccumulatedLength() << std::endl;

            std::vector<std::shared_ptr<Path>> neighbors = getNextNeighbors(lastPath);
            for (std::shared_ptr<Path> next: neighbors) {
                PathSequence newPathSeq(topPathSeq);
                newPathSeq.addPath(next);
                pathSequenceQueue.emplace(newPathSeq);
            }

        }

        return {};
    }

    std::vector<std::shared_ptr<Path>> PathFinder::getNextNeighbors(const std::shared_ptr<Path> &lastPath) {
        std::vector<std::shared_ptr<Path>> nextNeighbors;
        for (auto p: startSeekerPaths) {
            if (lastPath == p) {
                continue;
            }
            if (p->A == lastPath->B) {
                nextNeighbors.emplace_back(p);
            }
        }

        for (auto &[oid, paths]: startObjPaths) {
            for (std::shared_ptr<Path> p: paths) {
                if (lastPath->B == p->A) {
                    nextNeighbors.emplace_back(p);
                }
            }
        }

        for (auto &[oid, paths]: endObjPaths) {
            for (std::shared_ptr<Path> p: paths) {
                if (lastPath == p) {
                    continue;
                }
                if (lastPath->B == p->A) {
                    nextNeighbors.emplace_back(p);
                }
            }
        }

        for (auto p: arcPaths) {
            if (lastPath == p) {
                continue;
            }
            if (p->A == lastPath->B) {
                nextNeighbors.emplace_back(p);
            }
        }

        return nextNeighbors;
    }

    const std::vector<std::shared_ptr<Path>> &PathFinder::getSeekerPaths() const {
        return startSeekerPaths;
    }

    const ObstaclePathMap &PathFinder::getStartObjPaths() const {
        return startObjPaths;
    }

    const std::vector<std::shared_ptr<Path>> &PathFinder::getArcPaths() const {
        return arcPaths;
    }


}