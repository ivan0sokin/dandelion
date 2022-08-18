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
        virtual ~Shader() noexcept = default;

    protected:
        Shader() noexcept = default;
    };

    class DANDELION_API VertexShader : public Shader {
    public:
        ~VertexShader() noexcept override = default;

    protected:
        VertexShader() noexcept = default;
    };

    class DANDELION_API FragmentShader : public Shader {
    public:
        ~FragmentShader() noexcept override = default;

    protected:
        FragmentShader() noexcept = default;
    };

}

#endif