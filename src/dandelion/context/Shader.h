#ifndef DANDELION_SHADER_H
#define DANDELION_SHADER_H

#include "../core/Core.h"

#include <vector>
#include <span>
#include <filesystem>

namespace Dandelion {

    enum class ShaderType {
        Vertex = 0,
        Fragment
    };

    class DANDELION_API Shader {
    public:
        Shader() noexcept = delete;

        constexpr Shader(const ShaderType &type) noexcept : mType(type) {}

        virtual ~Shader() noexcept = default;

        constexpr ShaderType Type() const noexcept { return mType; };

        virtual void LoadDataFromFile(const std::filesystem::path &filePath) noexcept = 0;

        virtual bool Assemble() noexcept = 0;

    protected:
        ShaderType mType;
    };

}

#endif