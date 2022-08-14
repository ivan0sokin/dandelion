#ifndef DANDELION_GLSHADER_H
#define DANDELION_GLSHADER_H

#include "../Shader.h"

#include <glad/glad.h>

#include <optional>

namespace Dandelion {

    class DANDELION_API GLShader : public Shader {
    public:
        GLShader() noexcept = default;

        inline GLShader(const ShaderType &type) noexcept : Shader(type) {}

        ~GLShader() noexcept override = default;

        void LoadDataFromFile(const std::filesystem::path &filePath) noexcept override;

        bool Assemble() noexcept override;

        constexpr GLuint ID() noexcept { return mID; }

    private:
        std::optional<GLenum> DetermineShaderType() const noexcept;

        void CreateShaderObject(GLenum shaderType) noexcept;

        void LoadShaderData() const noexcept;

        std::optional<std::string> CompileShader() const noexcept;

    private:
        std::vector<char> mData;
        GLuint mID;
    };

}


#endif