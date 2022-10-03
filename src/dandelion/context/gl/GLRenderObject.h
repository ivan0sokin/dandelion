#ifndef DANDELION_GLRENDEROBJECT_H
#define DANDELION_GLRENDEROBJECT_H

#include "../RenderObject.h"

#include <glad/glad.h>

namespace Dandelion {

    class DANDELION_API GLRenderObject : public RenderObject {
    public:
        GLRenderObject(std::initializer_list<std::shared_ptr<VertexBuffer>> vertexBuffers, std::shared_ptr<IndexBuffer> indexBuffer) noexcept;

        ~GLRenderObject() noexcept override;

        void Draw(std::size_t vertexCount) noexcept override;

        void DrawIndexed(std::size_t vertexCount) noexcept override;

    private:
        void CreateArrayObject() noexcept;

        void Bind() noexcept;

        void Unbind() noexcept;

        void LoadDataIntoBuffers() noexcept;

        void UnbindIndexBuffer() noexcept;

    private:
        GLuint mID;
    };

}

#endif