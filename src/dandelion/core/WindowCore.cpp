#include "WindowCore.h"
#include "Logger.h"

#include <GLFW/glfw3.h>

namespace Dandelion {
    bool WindowCore::Initialize() noexcept {
        if (glfwInit() == GLFW_FALSE) {
            return false;
        }

        glfwSetErrorCallback([](int, const char *description) {
            coreLogger.Log(LogLevel::Error, description);
        });

        return mIsInitialized = true;
    }

    void WindowCore::Terminate() noexcept {
        if (mIsInitialized) {
            glfwTerminate();
        }
    }

    std::shared_ptr<WindowCore> WindowCore::Instance() noexcept {
        static std::shared_ptr<WindowCore> instance{new WindowCore};
        return instance;
    }
}