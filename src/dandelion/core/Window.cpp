#include "Window.h"

#include "Logger.h"

namespace Dandelion {

    bool Window::Initialize() noexcept {
        return isInitialized = static_cast<bool>(glfwInit());
    }

    void Window::Terminate() noexcept {
        if (isInitialized) {
            glfwTerminate();
        }
    }

}