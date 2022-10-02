#ifndef DANDELION_TIMER_H
#define DANDELION_TIMER_H

#include "Core.h"

#include <chrono>

namespace Dandelion {

    class DANDELION_API Timer
    {
        using TimePoint = std::chrono::high_resolution_clock::time_point;
    public:
        Timer() noexcept;

        ~Timer() noexcept = default;

        void Reset() noexcept;

        void Update() noexcept;

        constexpr double Elapsed() const noexcept { return mElapsed; };

    private:
        TimePoint mCurrentTick, mLastTick;
        double mElapsed = 0;
    };
}


#endif