#ifndef DANDELION_GLSHADERPROGRAM_H
#define DANDELION_GLSHADERPROGRAM_H

#include "../ShaderProgram.h"

#include <glad/glad.h>

namespace Dandelion {

    class DANDELION_API GLShaderProgram : public ShaderProgram {
    public:
        GLShaderProgram() noexcept = default;

        ~GLShaderProgram() noexcept override = default;

        void AttachShader(std::shared_ptr<Shader> shader) noexcept override;

        void Assemble() noexcept override;

        void Activate() noexcept override;

    private:
        void AttachShaders() const noexcept;

        void DetachShaders() const noexcept;

        void DeleteShaders() const noexcept;

    private:
        GLuint mID;
        std::vector<GLuint> mShaderIDs;
    };

}

#endif