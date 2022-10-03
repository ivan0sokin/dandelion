#include "GLRenderObject.h"
#include "GLBuffer.h"

namespace Dandelion {

    GLRenderObject::GLRenderObject(std::initializer_list<std::shared_ptr<VertexBuffer>> vertexBuffers, std::shared_ptr<IndexBuffer> indexBuffer) noexcept : RenderObject(vertexBuffers, indexBuffer) {
        this->CreateArrayObject();

        this->Bind();
        this->LoadDataIntoBuffers();
        this->Unbind();
        this->UnbindIndexBuffer();
    }

    GLRenderObject::~GLRenderObject() noexcept {
        glDeleteVertexArrays(1, &mID);
    }

    void GLRenderObject::CreateArrayObject() noexcept {
        glGenVertexArrays(1, &mID);
    }

    void GLRenderObject::LoadDataIntoBuffers() noexcept {
        for (const auto &buffer : mVertexBuffers) {
            auto vertexBuffer = std::static_pointer_cast<GLVertexBuffer>(buffer);
            vertexBuffer->Bind();
            vertexBuffer->CopyData();
            vertexBuffer->DescribeVertexAttributes();
            vertexBuffer->Unbind();
        }

        if (mIndexBuffer) {
            auto indexBuffer = std::static_pointer_cast<GLIndexBuffer>(mIndexBuffer);
            indexBuffer->Bind();
            indexBuffer->CopyData();
        }
    }

    void GLRenderObject::UnbindIndexBuffer() noexcept {
        if (mIndexBuffer) {
            std::static_pointer_cast<GLIndexBuffer>(mIndexBuffer)->Unbind();
        }
    }

    void GLRenderObject::Bind() noexcept {
        glBindVertexArray(mID);
    }

    void GLRenderObject::Unbind() noexcept {
        glBindVertexArray(0);
    }

    void GLRenderObject::Draw(std::size_t vertexCount) noexcept {
        this->Bind();

        glDrawArrays(GL_TRIANGLES, static_cast<GLint>(0), static_cast<GLsizei>(vertexCount));

        this->Unbind();
    }

    void GLRenderObject::DrawIndexed(std::size_t vertexCount) noexcept {
        this->Bind();

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertexCount), GL_UNSIGNED_INT, nullptr);

        this->Unbind();
    }

}