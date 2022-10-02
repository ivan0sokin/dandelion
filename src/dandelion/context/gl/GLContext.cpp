#include "GLContext.h"
#include "../../core/Logger.h"

#include "GLShader.h"
#include "GLProgram.h"
#include "GLBuffer.h"
#include "GLRenderObject.h"

namespace Dandelion {

    bool GLContext::Initialize() noexcept {
        mWindow->MakeContextCurrent();

        if (!this->InitializeGlad()) {
            CoreLogger::Instance()->Log(LogLevel::Error, "Failed to load OpenGL");
        } else {
            CoreLogger::Instance()->Log(LogLevel::Info, "OpenGL loaded");
        }

        CoreLogger::Instance()->Log(LogLevel::Info, "OpenGL context created");

        return true;
    }

    void GLContext::Destroy() noexcept {
        CoreLogger::Instance()->Log(LogLevel::Info, "OpenGL context destroyed");
    }

    bool GLContext::InitializeGlad() noexcept {
        return static_cast<bool>(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
    }

    std::shared_ptr<Shader> GLContext::CreateVertexShader(const std::filesystem::path &filePath) noexcept {
        return this->CreateShader(filePath, GL_VERTEX_SHADER);
    }

    std::shared_ptr<Shader> GLContext::CreateFragmentShader(const std::filesystem::path &filePath) noexcept {
        return this->CreateShader(filePath, GL_FRAGMENT_SHADER);
    }

    std::shared_ptr<Shader> GLContext::CreateShader(const std::filesystem::path &filePath, GLenum type) noexcept {
        auto shader = std::make_shared<GLShader>(filePath, type);

        auto error = shader->Assemble();
        if (error) {
            std::stringstream message;
            message << "Failed to assemble " << std::quoted(filePath.filename().string()) << " shader, error: " << error.value();

            CoreLogger::Instance()->Log(LogLevel::Critical, message.str());
        }

        return shader;
    }

    std::shared_ptr<Program> GLContext::CreateProgram(std::initializer_list<std::shared_ptr<Shader>> shaders) noexcept {
        return std::make_shared<GLProgram>(shaders);
    }

    std::shared_ptr<VertexBuffer> GLContext::CreateVertexBuffer(const void *data, std::size_t size, Layout layout) noexcept {
        return std::make_shared<GLVertexBuffer>(data, size, std::move(layout));
    }

    std::shared_ptr<IndexBuffer> GLContext::CreateIndexBuffer(const void *data, std::size_t size) noexcept {
        return std::make_shared<GLIndexBuffer>(data, size);
    }

    std::shared_ptr<RenderObject> GLContext::CreateRenderObject(std::initializer_list<std::shared_ptr<VertexBuffer>> vertexBuffers, std::shared_ptr<IndexBuffer> indexBuffer) noexcept {
        return std::make_shared<GLRenderObject>(vertexBuffers, std::move(indexBuffer));
    }

}