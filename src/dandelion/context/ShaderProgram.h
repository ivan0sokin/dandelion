#ifndef DANDELION_SHADERPROGRAM_H
#define DANDELION_SHADERPROGRAM_H

#include "Shader.h"

#include <memory>

namespace Dandelion {

    class DANDELION_API ShaderProgram {
    public:
        ShaderProgram() noexcept = default;

        virtual ~ShaderProgram() noexcept = default;

        virtual void AttachShader(std::shared_ptr<Shader> shader) noexcept = 0;

        virtual void Assemble() noexcept = 0;

        virtual void Activate() noexcept = 0;
    };

}

#endif