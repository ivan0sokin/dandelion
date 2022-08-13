#include "Window.h"
#include "Logger.h"

#include <iomanip>
#include <sstream>

namespace Dandelion {
    Window::~Window() noexcept {
        glfwDestroyWindow(mHandle);

        std::stringstream message;
        message << "Destroyed window " << std::quoted(mTitle);
        CoreLogger::Instance()->Log(LogLevel::Info, message.str());
    }

    void Window::SetHints() noexcept {
        for (auto [hint, value] : mHints) {
            glfwWindowHint(hint, value);
        }
    }

    void Window::Create() noexcept {
        this->SetHints();

        mHandle = glfwCreateWindow(mWidth, mHeight, mTitle.data(), nullptr, nullptr);

        std::stringstream message;
        message << "Window " << std::quoted(mTitle) << " with resolution " << mWidth << 'x' << mHeight << " was created";
        CoreLogger::Instance()->Log(LogLevel::Info, message.str());
    }

    void Window::PollEvents() noexcept {
        glfwPollEvents();
    }

    void Window::MakeContextCurrent() noexcept {
        glfwMakeContextCurrent(mHandle);

        glfwSwapInterval(0);

        std::stringstream message;
        message << "Current OpenGL context is set in window " << std::quoted(mTitle);
        CoreLogger::Instance()->Log(LogLevel::Info, message.str());
    }

    void Window::SwapBuffers() noexcept {
        glfwSwapBuffers(mHandle);
    }

    bool Window::ShouldBeClosed() noexcept {
        return glfwWindowShouldClose(mHandle);
    }

}