#include "FileSystem.h"
#include "../core/Logger.h"

#include <fstream>
#include <sstream>
#include <iomanip>

namespace Dandelion {

    std::optional<std::vector<char>> FileSystem::ReadFile(const std::filesystem::path &filePath, const DataType &dataType) noexcept {
        auto openMode = std::ios::in | std::ios::ate;
        if (dataType == DataType::Text) {
            openMode |= std::ios::binary;
        }

        auto fileStream = std::ifstream(filePath, openMode);

        if (!fileStream) {
            std::stringstream message;
            message << "Failed to open file " << std::quoted(filePath.string());
            CoreLogger::Instance()->Log(LogLevel::Error, message.str());

            return {};
        }

        auto dataSize = static_cast<std::size_t>(fileStream.tellg());
        std::vector<char> buffer(dataSize);

        fileStream.seekg(0).read(buffer.data(), dataSize);

        return buffer;
    }

}