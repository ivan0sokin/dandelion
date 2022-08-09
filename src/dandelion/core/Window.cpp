#include "Window.h"

namespace Dandelion {

    bool Window::Initialize() noexcept {
        return static_cast<bool>(glfwInit());
    }

    void Window::Terminate() noexcept {
        glfwTerminate();
    }

}