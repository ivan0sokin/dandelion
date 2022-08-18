#ifndef DANDELION_ENGINE_H
#define DANDELION_ENGINE_H

#include "Core.h"
#include "Window.h"
#include "../context/Context.h"

#include <memory>
#include <vector>

namespace Dandelion {

    class DANDELION_API Engine {
    public:
        Engine(Engine &) = delete;
        Engine& operator=(Engine const&) = delete;

        static std::shared_ptr<Engine> Instance() noexcept;

        ~Engine() noexcept = default;

        bool Initialize() noexcept;

        void Terminate() noexcept;

        std::shared_ptr<Context> CreateContext(std::shared_ptr<Window> window) noexcept;

        void SetActiveContext(std::shared_ptr<Context> context) noexcept;

        std::shared_ptr<Context> GetActiveContext() const noexcept;
    private:
        Engine() noexcept = default;

    private:
        std::shared_ptr<Context> mActiveContext;
    };

}

#endif