#include "kaliatech-pather-lib/MapFileUtils.h"
#include "kaliatech-pather-lib/Map.h"

#include <iostream>
#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>

namespace kpath {

    using namespace nlohmann;

    /**
     *
     * @param filePath
     * @throw std::exception if file does not exist
     * @return
     */
    std::unique_ptr<Map> MapFileUtils::load(const std::filesystem::path &filePath) {

        if (!std::filesystem::exists(filePath)) {
            throw std::exception("File does not exist");
        }

        std::ifstream ifs(filePath);
        json jf = json::parse(ifs);
        ifs.close();

        int width = jf["map"]["width"];
        int height = jf["map"]["height"];

        json objJson = jf["map"]["obstacles"];

        std::vector<Obstacle> obstacles;

        for (json::iterator it = objJson.begin(); it != objJson.end(); ++it) {
            json j = *it;
            Obstacle o(j["id"], j["x"], j["y"], j["r"]);
            obstacles.push_back(o);
        }

        std::unique_ptr<Map> map(new Map(width, height, obstacles));
        return map;
    }

    void MapFileUtils::save(const Map &map, const std::filesystem::path &filePath) {

        json jf;

        json jMap = json::object();
        jMap["width"] = map.getWidth();
        jMap["height"] = map.getHeight();

        json jObs = json::array();
        for(auto o : map.getObstacles()) {
            json jo = json::object();
            jo["id"] = o.getId();
            jo["x"] = o.x;
            jo["y"] = o.y;
            jo["r"] = o.r;
            jObs.push_back(jo);
        }
        jMap["obstacles"] = jObs;
        jf["map"] = jMap;

        std::ofstream file(filePath);
        file << jf;
        file.close();
    }
}
