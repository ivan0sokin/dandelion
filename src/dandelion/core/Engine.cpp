#include "Engine.h"

#include "Window.h"
#include "Logger.h"

namespace Dandelion {

    std::shared_ptr<Engine> Engine::Instance() noexcept {
        static std::shared_ptr<Engine> instance{new Engine};
        return instance;
    }

    bool Engine::Initialize() noexcept {
        coreLogger.Create();

        if (!Window::Initialize()) {
            coreLogger.Log(LogLevel::Error, "Could not initialize Window");
            return false;
        } else {
            coreLogger.Log(LogLevel::Info, "Window initialized");
        }

        coreLogger.Log(LogLevel::Info, "Engine initialized");

        return true;
    }

    void Engine::Terminate() noexcept {
        Window::Terminate();
        coreLogger.Log(LogLevel::Info, "Window terminated");

        coreLogger.Log(LogLevel::Info, "Engine terminated");
    }

}