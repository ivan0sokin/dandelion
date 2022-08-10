#include "Window.h"
#include "Logger.h"

namespace Dandelion {
    Window::~Window() noexcept {
        glfwDestroyWindow(mHandle);
    }

    void Window::SetHints() noexcept {
        for (auto [hint, value] : mHints) {
            glfwWindowHint(hint, value);
        }
    }

    void Window::Create() noexcept {
        this->SetHints();

        mHandle = glfwCreateWindow(mWidth, mHeight, mTitle.data(), nullptr, nullptr);
    }

    void Window::PollEvents() noexcept {
        glfwPollEvents();
    }

    void Window::MakeCurrent() noexcept {
        glfwMakeContextCurrent(mHandle);
    }

}