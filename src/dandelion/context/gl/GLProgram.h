#ifndef DANDELION_GLPROGRAM_H
#define DANDELION_GLPROGRAM_H

#include "../Program.h"

#include <vector>

#include <glad/glad.h>

namespace Dandelion {

    class DANDELION_API GLProgram : public Program {
    public:
        GLProgram(std::initializer_list<std::shared_ptr<Shader>> shaders) noexcept;

        ~GLProgram() noexcept override;

        void Enable() noexcept override;

        void Disable() noexcept override;

    private:
        void Compile() noexcept;

        void AttachShaders() const noexcept;

        void DetachShaders() const noexcept;

        void DeleteShaders() const noexcept;

    private:
        GLuint mID;
        std::vector<GLuint> mShaderIDs;
    };

}

#endif