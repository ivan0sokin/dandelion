#ifndef DANDELION_FILESYSTEM_H
#define DANDELION_FILESYSTEM_H

#include "../core/Core.h"

#include <filesystem>
#include <optional>

namespace Dandelion {

    enum class DataType {
        Text = 0,
        Binary
    };

    class DANDELION_API FileSystem {
    public:
        FileSystem() = delete;

        ~FileSystem() = delete;

        static std::optional<std::vector<char>> ReadFile(const std::filesystem::path &filePath, const DataType &dataType) noexcept;
    };

}

#endif