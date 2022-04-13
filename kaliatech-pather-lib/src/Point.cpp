#include "kaliatech-pather-lib/Point.h"

#include <string>
#include <sstream>

namespace kpath {
    std::string Point::toString() {
        std::ostringstream str;
        str << "x:" << x << ",y:" << y;
        return str.str();
    }
}