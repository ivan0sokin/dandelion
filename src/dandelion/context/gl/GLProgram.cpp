#include "GLProgram.h"
#include "GLShader.h"

namespace Dandelion {

    GLProgram::GLProgram(std::initializer_list<std::shared_ptr<Shader>> shaders) noexcept : Program(shaders) {
        for (const auto &shader : mShaders) {
            mShaderIDs.push_back(std::static_pointer_cast<GLShader>(shader)->ID());
        }

        this->Compile();
    }

    void GLProgram::Compile() noexcept {
        mID = glCreateProgram();

        this->AttachShaders();

        glLinkProgram(mID);

        this->DetachShaders();

        this->DeleteShaders();
    }

    void GLProgram::AttachShaders() const noexcept {
        for (auto shaderID : mShaderIDs) {
            glAttachShader(mID, shaderID);
        }
    }

    void GLProgram::DetachShaders() const noexcept {
        for (auto shaderID : mShaderIDs) {
            glDetachShader(mID, shaderID);
        }
    }

    void GLProgram::DeleteShaders() const noexcept {
        for (auto shaderID : mShaderIDs) {
            glDeleteShader(shaderID);
        }
    }

    void GLProgram::Enable() noexcept {
        glUseProgram(mID);
    }

    void GLProgram::Disable() noexcept {
        glUseProgram(0);
    }

    GLProgram::~GLProgram() noexcept {
        glDeleteProgram(mID);
    }

}