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
}

#endif