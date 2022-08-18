#ifndef DANDELION_GLSHADER_H
#define DANDELION_GLSHADER_H

#include "../Shader.h"

#include <glad/glad.h>

#include <optional>
#include <vector>
#include <span>

namespace Dandelion {

    class DANDELION_API GLShader : public Shader {
    public:

        inline GLShader(std::filesystem::path filePath) noexcept : mFilePath(std::move(filePath)) {}

        ~GLShader() noexcept override = default;

        std::optional<std::string> Assemble() noexcept;

        constexpr GLuint ID() noexcept { return mID; }

    private:
        GLShader() noexcept = default;

        virtual constexpr GLenum GetShaderType() const noexcept = 0;

        void CreateShaderObject() noexcept;

        std::optional<std::vector<char>> LoadDataFromFile() const noexcept;

        void LoadShaderData(std::span<char> data) const noexcept;

        std::optional<std::string> CompileShader() const noexcept;

    private:
        std::filesystem::path mFilePath;
        GLuint mID;
    };

    class DANDELION_API GLVertexShader : public GLShader {
    public:
        GLVertexShader(std::filesystem::path filePath) : GLShader(std::move(filePath)) {}

        ~GLVertexShader() noexcept override = default;

    private:
        GLVertexShader() noexcept = delete;

        constexpr GLenum GetShaderType() const noexcept override { return GL_VERTEX_SHADER; }
    };

    class DANDELION_API GLFragmentShader : public GLShader {
    public:
        GLFragmentShader(std::filesystem::path filePath) : GLShader(std::move(filePath)) {}

        ~GLFragmentShader() noexcept override = default;

    private:
        GLFragmentShader() noexcept = delete;

        constexpr GLenum GetShaderType() const noexcept override { return GL_VERTEX_SHADER; }
    };

}


#endif