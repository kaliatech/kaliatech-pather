#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "kaliatech-pather-lib/MapFileUtils.h"
#include "kaliatech-pather-lib/PathFinder.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: KaliatechPatherAppConsole <map-file>" << std::endl;
        std::cerr << "Missing map-file argument" << std::endl;
        return EXIT_FAILURE;
    }

    std::string mapFilePath = argv[1];
    std::unique_ptr<kpath::Map> map;
    try {
        map = kpath::MapFileUtils::load(mapFilePath);
    }
    catch (const std::runtime_error &e) {
        std::cerr << "Error loading map. Message: " << e.what();
        return EXIT_FAILURE;
    }

    kpath::Seeker seeker(10, 10, 10);
    kpath::Target target(300, 300, 10);

    kpath::PathFinder pFinder;
    kpath::PathSequence pSequence = pFinder.find(*map, seeker, target);

    if (pSequence.getPaths().empty()) {
        std::cout << "Path could not be found." << std::endl;
        return EXIT_SUCCESS;
    }

    std::cout << "Path:" << std::endl;
    for (const auto &path: pSequence.getPaths()) {
        std::cout << "   " << path->toString() << std::endl;
    }


    return EXIT_SUCCESS;
}