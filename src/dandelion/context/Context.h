#ifndef DANDELION_CONTEXT_H
#define DANDELION_CONTEXT_H

#include "RenderObject.h"

#include <memory>
#include <filesystem>

namespace Dandelion {

    class DANDELION_API Context {
    public:
        virtual ~Context() noexcept = default;

        virtual bool Initialize() noexcept = 0;

        virtual void Destroy() noexcept = 0;

        virtual std::shared_ptr<Shader> CreateVertexShader(const std::filesystem::path &filePath) noexcept = 0;

        virtual std::shared_ptr<Shader> CreateFragmentShader(const std::filesystem::path &filePath) noexcept = 0;

        virtual std::shared_ptr<Program> CreateProgram(std::initializer_list<std::shared_ptr<Shader>> shaders) noexcept = 0;

        virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(const void *data, std::size_t size, Layout bufferLayout) noexcept = 0;

        virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(const void *data, std::size_t size) noexcept = 0;

        virtual std::shared_ptr<RenderObject> CreateRenderObject(std::initializer_list<std::shared_ptr<VertexBuffer>> vertexBuffers, std::shared_ptr<IndexBuffer> indexBuffer) noexcept = 0;
    };

}

#endif