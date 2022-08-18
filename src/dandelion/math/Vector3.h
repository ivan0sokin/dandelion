#ifndef DANDELION_VECTOR3_H
#define DANDELION_VECTOR3_H

#include "../core/Core.h"

namespace Dandelion {

    template<typename T>
    class DANDELION_API Vector3 {
    public:
        Vector3() noexcept = default;

        constexpr Vector3(T scalar) noexcept : mX(scalar), mY(scalar), mZ(scalar) {}

        constexpr Vector3(T x, T y, T z) noexcept : mX(x), mY(y), mZ(z) {}

        ~Vector3() noexcept = default;

        constexpr T x() const noexcept { return mX; }

        constexpr T y() const noexcept { return mY; }

        constexpr T z() const noexcept { return mZ; }

        constexpr T r() const noexcept { return mX; }

        constexpr T g() const noexcept { return mY; }

        constexpr T b() const noexcept { return mZ; }
    private:
        T mX, mY, mZ;
    };

    using Vector3f = Vector3<float>;
    using Color3f = Vector3<float>;
}

#endif