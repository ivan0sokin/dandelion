#include "FileSystem.h"
#include "../core/Logger.h"

#include <fstream>
#include <sstream>

namespace Dandelion {

    std::optional<std::vector<char>> FileSystem::ReadFile(const std::filesystem::path &filePath, const DataType &dataType) noexcept {
        auto openMode = std::ios::in | std::ios::ate;
        if (dataType == DataType::Binary) {
            openMode |= std::ios::binary;
        }

        auto fileStream = std::ifstream(filePath, openMode);
        if (!fileStream) {
            return {};
        }

        std::vector<char> buffer;
        buffer.reserve(fileStream.tellg());

        fileStream.seekg(0, std::ios::beg);
        buffer.assign((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

        return buffer;
    }

}