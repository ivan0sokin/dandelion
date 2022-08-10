#include "Engine.h"
#include "Logger.h"
#include "WindowCore.h"

namespace Dandelion {

    std::shared_ptr<Engine> Engine::Instance() noexcept {
        static std::shared_ptr<Engine> instance{new Engine};
        return instance;
    }

    bool Engine::Initialize() noexcept {
        coreLogger.Create();

        if (!WindowCore::Instance()->Initialize()) {
            coreLogger.Log(LogLevel::Error, "Could not initialize Window Core");
            return false;
        } else {
            coreLogger.Log(LogLevel::Info, "Window Core initialized");
        }

        coreLogger.Log(LogLevel::Info, "Engine initialized");

        return true;
    }

    void Engine::Terminate() noexcept {
        WindowCore::Instance()->Terminate();
        coreLogger.Log(LogLevel::Info, "Window Core terminated");

        coreLogger.Log(LogLevel::Info, "Engine terminated");
    }

}