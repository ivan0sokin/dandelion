#ifndef DANDELION_GLCONTEXT_H
#define DANDELION_GLCONTEXT_H

#include "../Context.h"
#include "../../core/Window.h"

namespace Dandelion {

    class DANDELION_API GLContext : public Context {
    public:
        GLContext() noexcept = default;

        inline GLContext(std::shared_ptr<Window> window) noexcept : mWindow(window) {}

        ~GLContext() noexcept override = default;

        bool Create() noexcept override;

        void Destroy() noexcept override;

        std::shared_ptr<Shader> CreateShader(const ShaderType &type) noexcept override;

        std::shared_ptr<ShaderProgram> CreateShaderProgram() noexcept override;

    private:
        bool InitializeGlad() noexcept;

    private:
        std::shared_ptr<Window> mWindow;
    };

}


#endif