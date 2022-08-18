#ifndef DANDELION_CONTEXT_H
#define DANDELION_CONTEXT_H

#include "ShaderProgram.h"

#include <memory>

namespace Dandelion {

    class DANDELION_API Context {
    public:
        Context() noexcept = default;

        virtual ~Context() noexcept = default;

        virtual bool Create() noexcept = 0;

        virtual void Destroy() noexcept = 0;

        virtual std::shared_ptr<Shader> CreateShader(const std::filesystem::path &filePath, const ShaderType &type) noexcept = 0;

        virtual std::shared_ptr<ShaderProgram> CreateShaderProgram() noexcept = 0;
    };

}

#endif