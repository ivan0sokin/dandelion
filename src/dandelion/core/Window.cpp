#include "Window.h"
#include "Logger.h"
#include "input/Mouse.h"
#include "input/MouseEvent.h"

#include <iomanip>
#include <sstream>

namespace Dandelion {

    std::shared_ptr<MainWindow> MainWindow::Instance() noexcept {
        static std::shared_ptr<MainWindow> instance{new MainWindow};
        return instance;
    }

    void MainWindow::SetInitialParameters(const WindowParameters &initialParameters) noexcept {
        mInitialParameters = initialParameters;
    }

    void Window::Destroy() noexcept {
        glfwDestroyWindow(mHandle);

        std::stringstream message;
        message << "Destroyed window " << std::quoted(mInitialParameters.title);
        CoreLogger::Instance()->Log(LogLevel::Info, message.str());
    }

    void Window::Create() noexcept {
        this->SetHints();

        auto [title, width, height] = mInitialParameters;
        mHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        std::stringstream message;
        message << "Window " << std::quoted(title) << " with resolution " << width << 'x' << height << " was created";
        CoreLogger::Instance()->Log(LogLevel::Info, message.str());

        this->SetMouseCallbacks();
    }

    void Window::SetHints() noexcept {
        for (auto [hint, value] : mHints) {
            glfwWindowHint(hint, value);
        }
    }

    void Window::SetMouseCallbacks() noexcept {
        glfwSetCursorPosCallback(mHandle, [](GLFWwindow *handle, double x, double y) {
            Mouse::Instance()->mEventQueue->Push<MouseMoveEvent>(x, y);
        });

        glfwSetScrollCallback(mHandle, [](GLFWwindow *handle, double xOffset, double yOffset) {
            Mouse::Instance()->mEventQueue->Push<MouseScrollEvent>(xOffset, yOffset);
        });
    }

    void Window::Show() noexcept {
        glfwShowWindow(mHandle);
    }

    void Window::Hide() noexcept {
        glfwHideWindow(mHandle);
    }

    void Window::PollEvents() noexcept {
        Mouse::Instance()->mEventQueue->ClearHandled();

        glfwPollEvents();
    }

    void Window::MakeContextCurrent() noexcept {
        glfwMakeContextCurrent(mHandle);

        glfwSwapInterval(0);

        std::stringstream message;
        message << "Current OpenGL context is set in window " << std::quoted(mInitialParameters.title);
        CoreLogger::Instance()->Log(LogLevel::Info, message.str());
    }

    void Window::SwapBuffers() noexcept {
        glfwSwapBuffers(mHandle);
    }

    bool Window::ShouldBeClosed() const noexcept {
        return glfwWindowShouldClose(mHandle);
    }

    std::pair<unsigned int, unsigned int> Window::GetFrameBufferSize() const noexcept {
        std::pair<int, int> frameBufferSize;
        glfwGetFramebufferSize(mHandle, &frameBufferSize.first, &frameBufferSize.second);

        return frameBufferSize;
    }

    unsigned int Window::GetFrameBufferWidth() const noexcept {
        int frameBufferWidth;
        glfwGetFramebufferSize(mHandle, &frameBufferWidth, nullptr);

        return frameBufferWidth;
    }

    unsigned int Window::GetFrameBufferHeight() const noexcept {
        int frameBufferHeight;
        glfwGetFramebufferSize(mHandle, &frameBufferHeight, nullptr);

        return frameBufferHeight;
    }


    std::pair<unsigned int, unsigned int> Window::GetSize() const noexcept {
        std::pair<int, int> size;
        glfwGetWindowSize(mHandle, &size.first, &size.second);

        return size;
    }

}