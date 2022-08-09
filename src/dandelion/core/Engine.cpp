#include "Engine.h"
#include "Window.h"

namespace Dandelion {

    std::shared_ptr<Engine> Engine::Instance() noexcept {
        static std::shared_ptr<Engine> instance{new Engine};
        return instance;
    }

    bool Engine::Initialize() noexcept {
        if (!Window::Initialize()) {
            return false;
        }

        return true;
    }

    void Engine::Terminate() noexcept {
        Window::Terminate();
    }

}