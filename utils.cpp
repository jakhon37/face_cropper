// utils.cpp
#include "utils.h"
#include <filesystem>

namespace utils {

    bool createDirectory(const std::string& path) {
        try {
            if (!std::filesystem::exists(path)) {
                return std::filesystem::create_directories(path);
            }
            return true;
        } catch (const std::filesystem::filesystem_error&) {
            return false;
        }
    }

}
