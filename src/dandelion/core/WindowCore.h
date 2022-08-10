#ifndef DANDELION_WINDOWCORE_H
#define DANDELION_WINDOWCORE_H

#include <memory>

namespace Dandelion {

    class WindowCore {
    public:
        WindowCore(WindowCore &) = delete;
        WindowCore& operator=(WindowCore const&) = delete;

        static std::shared_ptr<WindowCore> Instance() noexcept;

        ~WindowCore() noexcept = default;

        bool Initialize() noexcept;

        void Terminate() noexcept;
    private:
        WindowCore() noexcept = default;

    private:
        bool mIsInitialized = false;
    };
}

#endif