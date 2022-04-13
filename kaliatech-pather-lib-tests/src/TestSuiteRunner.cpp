#include "MapFileUtilsTest.h"

#include <iostream>

int main(int argc, char *argv[]) {

    try {
        MapFileUtilsTest::runTests();
        std::cerr << "Success." << std::endl;
    }
    catch(const std::runtime_error & e) {
        std::cerr << "Failed. Message: " << e.what() << std::endl;
    }

    return 0;

}