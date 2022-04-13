#ifndef KALIATECH_PATHER_LIB_TEST_MAPFILEUTILS_H
#define KALIATECH_PATHER_LIB_TEST_MAPFILEUTILS_H

#include <iostream>

#include "kaliatech-pather-lib/MapFileUtils.h"


namespace MapFileUtilsTest {

    using namespace kpath;

    void runTest_ExpectException() {
        std::cout << "  runTest_ExpectException" << std::endl;
        try {
            auto map = MapFileUtils::load("test-does-not-exist.txt");
        }
        catch (const std::runtime_error& e) {
            std::string expected = e.what();
            assert(!expected.empty());
        }
    }

    void runTest_Load() {
        std::cout << "  runTest_Load" << std::endl;
        auto map = MapFileUtils::load("assets/test-map-1.json");
        if (map->getObstacles().size() != 2) {
            throw std::runtime_error("Load load not as expected2.");
        }
    }

    void runTest_Save() {
        std::cout << "  runTest_Save" << std::endl;
        std::vector<Obstacle> obstacles;
        obstacles.emplace_back("o1", 10.0f, 11.0f, 0.0f);
        Map map(10,10,obstacles);

        std::filesystem::path path = "assets/test-map-save.temp";
        MapFileUtils::save(map, path);
        if (!std::filesystem::exists(path)) {
            throw std::runtime_error("File did not exist after save.");
        }
        auto newMap = MapFileUtils::load(path);
        //std::filesystem::remove(path);
        if (map.getObstacles().size() != newMap->getObstacles().size()) {
            throw std::runtime_error("Reloaded map different than saved map.");
        }


    }

    void runTests() {
        std::cout << "MapFileUtilsTest Begin..." << std::endl;
        runTest_ExpectException();
        runTest_Load();
        runTest_Save();
        std::cout << "MapFileUtilsTest End." << std::endl;
    }
}

#endif // KALIATECH_PATHER_LIB_TEST_MAPFILEUTILS_H

