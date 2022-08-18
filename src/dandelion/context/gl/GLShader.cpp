#include "GLShader.h"
#include "../../core/Logger.h"
#include "../../filesystem/FileSystem.h"

namespace Dandelion {

    std::optional<std::string> GLShader::Assemble() noexcept {
        this->CreateShaderObject();

        auto shaderData = this->LoadDataFromFile();
        if (!shaderData) {
            std::stringstream message;
            message << "Failed to load shader data from file " << std::quoted(mFilePath.filename().string());

            return message.str();
        }

        this->LoadShaderData(std::span{shaderData->begin(), shaderData->end()});

        auto infoLog = this->CompileShader();
        if (infoLog) {
            std::stringstream message;
            message << "Failed to compile shader " << std::quoted(mFilePath.filename().string()) <<  ", log: " << infoLog.value();

            return message.str();
        }

        std::stringstream message;
        message << "Shader " << std::quoted(mFilePath.filename().string()) << " assembled";

        CoreLogger::Instance()->Log(LogLevel::Info, message.str());

        return {};
    }

    void GLShader::CreateShaderObject() noexcept {
        mID = glCreateShader(this->GetShaderType());
    }

    std::optional<std::vector<char>> GLShader::LoadDataFromFile() const noexcept {
        auto data = FileSystem::ReadFile(mFilePath, DataType::Text);
        if (!data) {
            return {};
        }

        return data.value();
    }

    void GLShader::LoadShaderData(std::span<char> data) const noexcept {
        auto source = data.data();
        auto length = static_cast<GLint>(data.size());
        glShaderSource(mID, 1, &source, &length);
    }

    std::optional<std::string> GLShader::CompileShader() const noexcept {
        glCompileShader(mID);

        GLint result;
        glGetShaderiv(mID, GL_COMPILE_STATUS, &result);

        constexpr static GLsizei MAX_INFO_LOG_LENGTH = 512;

        std::string infoLog;
        if (result == GL_FALSE) {
            infoLog.resize(MAX_INFO_LOG_LENGTH);
            glGetShaderInfoLog(mID, MAX_INFO_LOG_LENGTH, nullptr, infoLog.data());

            return infoLog;
        }

        return {};
    }

}