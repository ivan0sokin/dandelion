#ifndef DANDELION_RENDEROBJECT_H
#define DANDELION_RENDEROBJECT_H

#include "Buffer.h"
#include "Layout.h"
#include "Program.h"

#include <utility>
#include <vector>
#include <memory>

namespace Dandelion {

    class DANDELION_API RenderObject {
    public:
        virtual ~RenderObject() noexcept = default;

        inline RenderObject(std::initializer_list<std::shared_ptr<VertexBuffer>> vertexBuffers, std::shared_ptr<IndexBuffer> indexBuffer) noexcept :
            mVertexBuffers(vertexBuffers), mIndexBuffer(std::move(indexBuffer)) {}

        virtual void Draw(std::size_t vertexCount) noexcept = 0;

        virtual void DrawIndexed(std::size_t vertexCount) noexcept = 0;

    protected:
        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
        std::shared_ptr<IndexBuffer> mIndexBuffer;
    };

}

#endif