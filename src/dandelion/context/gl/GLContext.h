#ifndef DANDELION_GLCONTEXT_H
#define DANDELION_GLCONTEXT_H

#include "../Context.h"
#include "../../core/Window.h"

#include <glad/glad.h>

namespace Dandelion {

    class DANDELION_API GLContext : public Context {
    public:
        GLContext() noexcept = default;

        inline GLContext(std::shared_ptr<Window> window) noexcept : mWindow(window) {}

        ~GLContext() noexcept override = default;

        bool Initialize() noexcept override;

        void Destroy() noexcept override;

        std::shared_ptr<Shader> CreateVertexShader(const std::filesystem::path &filePath) noexcept override;

        std::shared_ptr<Shader> CreateFragmentShader(const std::filesystem::path &filePath) noexcept override;

        std::shared_ptr<Program> CreateProgram(std::initializer_list<std::shared_ptr<Shader>> shaders) noexcept override;

        std::shared_ptr<VertexBuffer> CreateVertexBuffer(const void *data, std::size_t size, Layout layout) noexcept override;

        std::shared_ptr<IndexBuffer> CreateIndexBuffer(const void *data, std::size_t size) noexcept override;

        std::shared_ptr<RenderObject> CreateRenderObject(std::initializer_list<std::shared_ptr<VertexBuffer>> vertexBuffers, std::shared_ptr<IndexBuffer> indexBuffer) noexcept override;

    private:
        bool InitializeGlad() noexcept;

        std::shared_ptr<Shader> CreateShader(const std::filesystem::path &filePath, GLenum type) noexcept;

    private:
        std::shared_ptr<Window> mWindow;
    };

}


#endif