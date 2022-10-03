#ifndef DANDELION_VECTOR2_H
#define DANDELION_VECTOR2_H

#include "../core/Core.h"

#include <cmath>

namespace Dandelion {

    template <typename T>
    class DANDELION_API Vector2 {
    public:
        constexpr ~Vector2() noexcept = default;

        constexpr Vector2() noexcept = default;

        constexpr Vector2(T x, T y) noexcept : mX(x), mY(y) {}

        constexpr Vector2(T scalar) noexcept : mX(scalar), mY(scalar) {}

        constexpr Vector2(const Vector2 &begin, const Vector2 &end) noexcept : mX(end.mX - begin.mX), mY(end.mY - begin.mY) {}

        constexpr T DotProduct(const Vector2 &other) const noexcept { return mX * other.mX + mY * other.mY; }

        constexpr T CrossProduct(const Vector2& other) const noexcept { return mX * other.mY - other.mX * mY; }

        constexpr T SquaredMagnitude() const noexcept { return mX * mX + mY * mY; }

        constexpr T Magnitude() const noexcept { return std::sqrt(this->SquaredMagnitude()); }

        constexpr Vector2 Normalize() const noexcept {
            return *this / this->Magnitude();
        }

        constexpr Vector2 operator+(T scalar) const noexcept {
            return {mX + scalar, mY + scalar};
        }

        constexpr Vector2 operator-(T scalar) const noexcept {
            return {mX - scalar, mY - scalar};
        }

        constexpr Vector2 operator*(T scalar) const noexcept {
            return {mX * scalar, mY * scalar};
        }

        constexpr Vector2 operator/(T scalar) const noexcept {
            return *this * (1 / scalar);
        }

        constexpr Vector2 operator+(const Vector2 &other) const noexcept {
            return {mX + other.mX, mY + other.mY};
        }

        constexpr Vector2 operator-(const Vector2 &other) const noexcept {
            return {mX - other.mX, mY - other.mY};
        }

    private:
        T mX, mY;
    };

    using Vector2f = Vector2<float>;
    using Color2f = Vector2<float>;
}

#endif