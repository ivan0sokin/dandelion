#include "GLBuffer.h"
#include "../../core/Logger.h"
#include <unordered_map>
#include <sstream>
namespace Dandelion {

    static std::unordered_map<Element, GLenum> elementTypes = {{Element::Float, GL_FLOAT}};

    GLBuffer::GLBuffer(GLenum target) noexcept : mTarget(target) {
        this->CreateBufferObject();
    }

    GLBuffer::~GLBuffer() noexcept {
        glDeleteBuffers(1, &mID);
    }

    void GLBuffer::CreateBufferObject() noexcept {
        glGenBuffers(1, &mID);
    }

    void GLBuffer::Bind() noexcept {
        glBindBuffer(mTarget, mID);
    }

    void GLBuffer::Unbind() noexcept {
        glBindBuffer(mTarget, 0);
    }

    void GLVertexBuffer::DescribeVertexAttributes() noexcept {
        for (auto [index, element, stride, offset] : mLayout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, static_cast<GLint>(Layout::ComponentCount(element)), elementTypes[Layout::ComponentType(element)], GL_FALSE, static_cast<GLsizei>(stride), (const void*)offset);
        }
    }

    void GLVertexBuffer::CopyData() noexcept {
        glBufferData(mTarget, static_cast<GLsizeiptr>(mSize), mData, GL_STATIC_DRAW);
    }

    void GLIndexBuffer::CopyData() noexcept {
        glBufferData(mTarget, static_cast<GLsizeiptr>(mSize), mData, GL_STATIC_DRAW);
    }
}