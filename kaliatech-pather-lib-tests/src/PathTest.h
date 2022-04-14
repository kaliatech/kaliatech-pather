#ifndef KALIATECH_PATHER_LIB_TEST_PATH_H
#define KALIATECH_PATHER_LIB_TEST_PATH_H

#include <iostream>
#include <numbers>

#include "kaliatech-pather-lib/Path.h"

namespace PathTest {
    using namespace kpath;

    void runTest_Angles() {
        std::cout << "  runTest_Angles" << std::endl;
        glm::vec2 A(5,5);
        glm::vec2 B(10,10);
        Path p("test", A, B);

        std::cout << "  DtoR:" << (180 / std::numbers::pi)  << std::endl;
        std::cout << "  angleR:" << p.AngleA() << std::endl;
        std::cout << "  angleD:" << p.AngleA() * (180 / std::numbers::pi)  << std::endl;

    }

    void runTests() {
        std::cout << "PathTest Begin..." << std::endl;
        runTest_Angles();
        std::cout << "PathTest End." << std::endl;
    }
}

#endif // KALIATECH_PATHER_LIB_TEST_PATH_H

