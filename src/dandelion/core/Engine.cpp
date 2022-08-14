#include "Engine.h"
#include "Logger.h"
#include "WindowCore.h"
#include "../context/gl/GLContext.h"

namespace Dandelion {

    std::shared_ptr<Engine> Engine::Instance() noexcept {
        static std::shared_ptr<Engine> instance{new Engine};
        return instance;
    }

    bool Engine::Initialize() noexcept {
        CoreLogger::Instance()->Register();

        if (!WindowCore::Instance()->Initialize()) {
            CoreLogger::Instance()->Log(LogLevel::Error, "Could not initialize Window Core");
            return false;
        } else {
            CoreLogger::Instance()->Log(LogLevel::Info, "Window Core initialized");
        }

        CoreLogger::Instance()->Log(LogLevel::Info, "Engine initialized");

        return true;
    }

    void Engine::Terminate() noexcept {
        WindowCore::Instance()->Terminate();
        CoreLogger::Instance()->Log(LogLevel::Info, "Window Core terminated");

        CoreLogger::Instance()->Log(LogLevel::Info, "Engine terminated");
    }

    std::shared_ptr<Context> Engine::CreateContext(std::shared_ptr<Window> window) {
        return std::make_shared<GLContext>(window);
    }

}