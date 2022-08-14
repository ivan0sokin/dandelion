#include "Window.h"
#include "Logger.h"

#include <iomanip>
#include <sstream>

namespace Dandelion {

    void Window::Destroy() noexcept {
        glfwDestroyWindow(mHandle);

        std::stringstream message;
        message << "Destroyed window " << std::quoted(mInitialParameters.title);
        CoreLogger::Instance()->Log(LogLevel::Info, message.str());
    }

    void Window::SetHints() noexcept {
        for (auto [hint, value] : mHints) {
            glfwWindowHint(hint, value);
        }
    }

    void Window::Create() noexcept {
        this->SetHints();

        auto [title, width, height] = mInitialParameters;
        mHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        std::stringstream message;
        message << "Window " << std::quoted(title) << " with resolution " << width << 'x' << height << " was created";
        CoreLogger::Instance()->Log(LogLevel::Info, message.str());
    }

    void Window::Show() noexcept {
        glfwShowWindow(mHandle);
    }

    void Window::Hide() noexcept {
        glfwHideWindow(mHandle);
    }

    void Window::PollEvents() noexcept {
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

    bool Window::ShouldBeClosed() noexcept {
        return glfwWindowShouldClose(mHandle);
    }

    void MainWindow::SetInitialParameters(const WindowParameters &initialParameters) noexcept {
        MainWindow::initialParameters = initialParameters;
    }

    std::shared_ptr<MainWindow> MainWindow::Instance() noexcept {
        static std::shared_ptr<MainWindow> instance{new MainWindow};
        return instance;
    }
}