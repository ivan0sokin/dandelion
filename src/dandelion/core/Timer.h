#ifndef DANDELION_TIMER_H
#define DANDELION_TIMER_H

#include "Core.h"

#include <chrono>

namespace Dandelion {

    template<typename T>
    class DANDELION_API Timer
    {
        using TimePoint = std::chrono::high_resolution_clock::time_point;
    public:
        Timer() noexcept;

        ~Timer() noexcept = default;

        void Reset() noexcept;

        void Update() noexcept;

        constexpr T Elapsed() const noexcept;

    private:
        TimePoint mCurrentTick, mLastTick;
        T mElapsed = 0;
    };

    template class DANDELION_API Timer<float>;
    template class DANDELION_API Timer<double>;
}


#endif