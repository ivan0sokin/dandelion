#include "Timer.h"

using namespace std::chrono;

namespace Dandelion {

    Timer::Timer() noexcept {
        this->Reset();
    }

    void Timer::Reset() noexcept {
        mLastTick = high_resolution_clock::now();
    }

    void Timer::Update() noexcept {
        mCurrentTick = high_resolution_clock::now();
        mElapsed = static_cast<duration<double, std::milli>>(mCurrentTick - mLastTick).count();

        mLastTick = mCurrentTick;
    }
}