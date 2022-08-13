#include "Timer.h"

using namespace std::chrono;

namespace Dandelion {

    template<typename T>
    Timer<T>::Timer() noexcept {
        this->Reset();
    }

    template<typename T>
    void Timer<T>::Reset() noexcept {
        mLastTick = high_resolution_clock::now();
    }

    template<typename T>
    void Timer<T>::Update() noexcept {
        mCurrentTick = high_resolution_clock::now();
        mElapsed = static_cast<duration<T, std::milli>>(mCurrentTick - mLastTick).count();

        mLastTick = mCurrentTick;
    }

    template<typename T>
    constexpr T Timer<T>::Elapsed() const noexcept {
        return mElapsed;
    }

}