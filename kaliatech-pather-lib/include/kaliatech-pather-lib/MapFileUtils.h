#ifndef KALIATECH_PATHER_LIB_MAPFILEUTILS_H
#define KALIATECH_PATHER_LIB_MAPFILEUTILS_H

#include <memory>
#include <filesystem>

#include "Map.h"

namespace kpath {

    /**
     * Utility methods for loading and saving maps.
     */
    class MapFileUtils {
    public:
        static std::unique_ptr<Map> load(const std::filesystem::path &filePath);

        static void save(const Map &map, const std::filesystem::path &filePath);
    };


}

#endif //KALIATECH_PATHER_LIB_MAPFILEUTILS_H
