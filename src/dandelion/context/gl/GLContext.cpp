#include "GLContext.h"
#include "../../core/Logger.h"
#include "GLShader.h"
#include "GLShaderProgram.h"

#include <glad/glad.h>

namespace Dandelion {

    bool GLContext::Create() noexcept {
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

    std::shared_ptr<Shader> GLContext::CreateShader(std::filesystem::path filePath, const ShaderType &type) noexcept {
        std::shared_ptr<GLShader> shader;
        switch (type) {
        case ShaderType::Vertex:
            shader = std::make_shared<GLVertexShader>(filePath);
            break;
        case ShaderType::Fragment:
            shader = std::make_shared<GLFragmentShader>(filePath);
            break;
        default:
            break;
        }

        auto error = shader->Assemble();
        if (error) {
            std::stringstream message;
            message << "Failed to assemble " << std::quoted(filePath.filename().string()) << " shader";

            CoreLogger::Instance()->Log(LogLevel::Critical, message.str());
        }

        return shader;
    }

    std::shared_ptr<ShaderProgram> GLContext::CreateShaderProgram() noexcept {
        return std::make_shared<GLShaderProgram>();
    }

}