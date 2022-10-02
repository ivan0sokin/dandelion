#ifndef DANDELION_GLSHADER_H
#define DANDELION_GLSHADER_H

#include "../Shader.h"

#include <glad/glad.h>

#include <filesystem>
#include <optional>
#include <utility>
#include <vector>
#include <span>

namespace Dandelion {

    class DANDELION_API GLShader : public Shader {
    public:
        GLShader(const std::filesystem::path &filePath, GLenum type) noexcept : mFilePath(filePath), mType(type) {}

        ~GLShader() noexcept override = default;

        std::optional<std::string> Assemble() noexcept;

        constexpr GLuint ID() noexcept { return mID; }

    private:
        void CreateShaderObject() noexcept;

        std::optional<std::vector<char>> LoadDataFromFile() const noexcept;

        void LoadShaderData(std::span<char> data) const noexcept;

        std::optional<std::string> CompileShader() const noexcept;

    private:
        std::filesystem::path mFilePath;
        GLenum mType;
        GLuint mID;
    };

}


#endif