#include "WindowCore.h"
#include "Logger.h"

#include <GLFW/glfw3.h>

namespace Dandelion {
    bool WindowCore::Initialize() noexcept {
        if (glfwInit() == GLFW_FALSE) {
            return false;
        }

        CoreLogger::Instance()->Log(LogLevel::Info, "GLFW initialized");

        this->SetCallbacks();

        return mIsInitialized = true;
    }

    void WindowCore::SetCallbacks() noexcept {
        glfwSetErrorCallback([](int, const char *description) {
            CoreLogger::Instance()->Log(LogLevel::Error, description);
        });
    }

    void WindowCore::Terminate() noexcept {
        if (mIsInitialized) {
            glfwTerminate();

            CoreLogger::Instance()->Log(LogLevel::Info, "GLFW terminated");
        }
    }

    std::shared_ptr<WindowCore> WindowCore::Instance() noexcept {
        static std::shared_ptr<WindowCore> instance{new WindowCore};
        return instance;
    }

}