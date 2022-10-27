#ifndef DANDELION_GLBUFFER_H
#define DANDELION_GLBUFFER_H

#include "../Buffer.h"

#include <glad/glad.h>

#include <utility>

namespace Dandelion {

    class DANDELION_API GLBuffer {
    public:
        GLBuffer(GLenum target) noexcept;

        ~GLBuffer() noexcept;

        constexpr GLuint ID() noexcept { return mID; }

        void Bind() noexcept;

        void Unbind() noexcept;

    private:
        void CreateBufferObject() noexcept;

    protected:
        GLenum mTarget;
        GLuint mID;
    };

    class DANDELION_API GLVertexBuffer : public GLBuffer, public VertexBuffer {
    public:
        inline GLVertexBuffer(const void *data, std::size_t size, Layout layout) noexcept : GLBuffer(GL_ARRAY_BUFFER), VertexBuffer(data, size, std::move(layout)) {}

        void CopyData() noexcept;

        void DescribeVertexAttributes() noexcept;

        ~GLVertexBuffer() noexcept override = default;
    };

    class DANDELION_API GLIndexBuffer : public GLBuffer, public IndexBuffer {
    public:
        inline GLIndexBuffer(const void *data, std::size_t size) noexcept : GLBuffer(GL_ELEMENT_ARRAY_BUFFER), IndexBuffer(data, size) {}

        void CopyData() noexcept;

        virtual ~GLIndexBuffer() noexcept override = default;
    };

    class DANDELION_API GLUniformBuffer : public GLBuffer, public UniformBuffer {
    public:
        GLUniformBuffer(const void *data, std::size_t size, std::size_t binding) noexcept;

        void AllocateMemory() noexcept;

        void SetSubData(const void *data, std::size_t offset, std::size_t size) noexcept override;

        virtual ~GLUniformBuffer() noexcept override = default;
    };

}

#endif