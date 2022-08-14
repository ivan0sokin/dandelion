#include "GLShader.h"
#include "../../core/Logger.h"
#include "../../filesystem/FileSystem.h"

namespace Dandelion {

    void GLShader::LoadDataFromFile(const std::filesystem::path &filePath) noexcept {
        auto data = FileSystem::ReadFile(filePath, DataType::Text);
        if (!data) {
            std::stringstream message;
            message << "Failed to load shader data from file " << std::quoted(filePath.string());
            CoreLogger::Instance()->Log(LogLevel::Error, message.str());

            return;
        }

        mData = data.value();
    }

    bool GLShader::Assemble() noexcept {
        auto shaderType = this->DetermineShaderType();
        if (!shaderType) {
            CoreLogger::Instance()->Log(LogLevel::Error, "Failed to determine shader type");
            return false;
        }

        this->CreateShaderObject(shaderType.value());
        this->LoadShaderData();

        auto message = this->CompileShader();
        if (message) {
            CoreLogger::Instance()->Log(LogLevel::Error, "Failed to compile shader, message: " + message.value());
            return false;
        }

        CoreLogger::Instance()->Log(LogLevel::Info, "Shader assembled");

        return true;
    }

    std::optional<GLenum> GLShader::DetermineShaderType() const noexcept {
        switch (mType) {
        case ShaderType::Vertex:
            return GL_VERTEX_SHADER;
        case ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;
        default:
            return {};
        }
    }

    void GLShader::CreateShaderObject(GLenum shaderType) noexcept {
        mID = glCreateShader(shaderType);
    }

    void GLShader::LoadShaderData() const noexcept {
        auto data = static_cast<const char *>(mData.data());
        glShaderSource(mID, 1, &data, nullptr);
    }

    std::optional<std::string> GLShader::CompileShader() const noexcept {
        glCompileShader(mID);

        GLint result;
        glGetShaderiv(mID, GL_COMPILE_STATUS, &result);

        constexpr static GLsizei MAX_INFO_LOG_LENGTH = 512;

        if (result == GL_FALSE) {
            std::string infoLog;
            infoLog.resize(MAX_INFO_LOG_LENGTH);
            glGetShaderInfoLog(mID, MAX_INFO_LOG_LENGTH, nullptr, infoLog.data());
            return infoLog;
        }

        return {};
    }

}