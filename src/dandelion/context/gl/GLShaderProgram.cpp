#include "GLShaderProgram.h"
#include "GLShader.h"

namespace Dandelion {

    void GLShaderProgram::AttachShader(std::shared_ptr<Shader> shader) noexcept {
        mShaderIDs.push_back(std::static_pointer_cast<GLShader>(shader)->ID());
    }

    void GLShaderProgram::Assemble() noexcept {
        mID = glCreateProgram();

        this->AttachShaders();

        glLinkProgram(mID);

        this->DetachShaders();

        this->DeleteShaders();
    }

    void GLShaderProgram::AttachShaders() const noexcept {
        for (auto shaderID : mShaderIDs) {
            glAttachShader(mID, shaderID);
        }
    }

    void GLShaderProgram::DetachShaders() const noexcept {
        for (auto shaderID : mShaderIDs) {
            glDetachShader(mID, shaderID);
        }
    }

    void GLShaderProgram::DeleteShaders() const noexcept {
        for (auto shaderID : mShaderIDs) {
            glDeleteShader(shaderID);
        }
    }

    void GLShaderProgram::Activate() noexcept {
        glUseProgram(mID);
    }

}