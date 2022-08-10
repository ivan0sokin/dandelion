#ifndef DANDELION_ENGINE_H
#define DANDELION_ENGINE_H

#include "Core.h"

#include <memory>

namespace Dandelion {

    class DANDELION_API Engine {
    public:
        Engine(Engine &) = delete;
        Engine& operator=(Engine const&) = delete;

        static std::shared_ptr<Engine> Instance() noexcept;

        ~Engine() noexcept = default;

        bool Initialize() noexcept;
        void Terminate() noexcept;

    private:
        Engine() noexcept = default;
    };

}

#endif