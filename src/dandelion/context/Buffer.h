#ifndef DANDELION_BUFFER_H
#define DANDELION_BUFFER_H

#include "../core/Core.h"
#include "Layout.h"

#include <cstdint>

namespace Dandelion {

    class DANDELION_API Buffer {
    public:
        inline Buffer(const void *data, std::size_t size) noexcept : mData(data), mSize(size) {}

        virtual ~Buffer() noexcept = default;

    protected:
        const void *mData;
        std::size_t mSize;
    };

    class DANDELION_API VertexBuffer : public Buffer {
    public:
        inline VertexBuffer(const void *data, std::size_t size, Layout layout) noexcept : Buffer(data, size), mLayout(layout) {}

        virtual ~VertexBuffer() noexcept override = default;

    protected:
        Layout mLayout;
    };

    class DANDELION_API IndexBuffer : public Buffer {
    public:
        inline IndexBuffer(const void *data, std::size_t size) noexcept : Buffer(data, size) {}

        virtual ~IndexBuffer() noexcept override = default;
    };

    class DANDELION_API UniformBuffer : public Buffer {
    public:
        inline UniformBuffer(const void *data, std::size_t size, std::size_t binding) noexcept : Buffer(data, size), mBinding(binding) {}

        virtual void SetSubData(const void *data, std::size_t offset, std::size_t size) noexcept = 0;

        inline void SetData(const void *data) noexcept { this->SetSubData(data, 0, mSize); }

        virtual ~UniformBuffer() noexcept override = default;

    protected:
        std::size_t mBinding;
    };

}

#endif