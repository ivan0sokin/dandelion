#ifndef DANDELION_VECTOR4_H
#define DANDELION_VECTOR4_H

#include "Vector3.h"

namespace Dandelion {

    template <typename T>
    class DANDELION_API Vector4 {
    public:
        constexpr ~Vector4() noexcept = default;

        constexpr Vector4() noexcept = default;

        constexpr Vector4(T x, T y, T z, T w) noexcept : mX(x), mY(y), mZ(z), mW(w) {}

        constexpr Vector4(T scalar) noexcept : mX(scalar), mY(scalar), mZ(scalar), mW(scalar) {}

        constexpr Vector4(const Vector4 &begin, const Vector4 &end) noexcept : mX(end.mX - begin.mX), mY(end.mY - begin.mY), mZ(end.mZ - begin.mZ), mW(end.mW - begin.mW) {}

        constexpr Vector4(const Vector2<T> &other, T z, T w) noexcept : mX(other.mX), mY(other.mY), mZ(z), mW(w) {}

        constexpr Vector4(T x, T y, const Vector2<T> &other) noexcept : mX(x), mY(y), mZ(other.mX), mW(other.mY) {}

        constexpr Vector4(T x, const Vector2<T> &other, T w) noexcept : mX(x), mY(other.mX), mZ(other.mY), mW(w) {}

        constexpr Vector4(const Vector3<T> &other, T w) noexcept : mX(other.mX), mY(other.mY), mZ(other.mZ), mW(w) {}

        constexpr Vector4(T x, const Vector3<T> &other) noexcept : mX(x), mY(other.mX), mZ(other.mY), mW(other.mZ) {}

        constexpr T DotProduct(const Vector4 &other) const noexcept { return mX * other.mX + mY * other.mY + mZ * other.mZ + mW * other.mW; }

        constexpr T SquaredMagnitude() const noexcept { return mX * mX + mY * mY + mZ * mZ + mW * mW; }

        constexpr T Magnitude() const noexcept { return std::sqrt(this->SquaredMagnitude()); }

        constexpr Vector4 Normalize() const noexcept {
            return *this / this->Magnitude();
        }

        constexpr Vector4 operator+(T scalar) const noexcept {
            return {mX + scalar, mY + scalar, mZ + scalar, mW + scalar};
        }

        constexpr Vector4 operator-(T scalar) const noexcept {
            return {mX - scalar, mY - scalar, mZ - scalar, mW - scalar};
        }

        constexpr Vector4 operator*(T scalar) const noexcept {
            return {mX * scalar, mY * scalar, mZ * scalar, mW * scalar};
        }

        constexpr Vector4 operator/(T scalar) const noexcept {
            return *this * (1 / scalar);
        }

        constexpr Vector4 operator+(const Vector4 &other) const noexcept {
            return {mX + other.mX, mY + other.mY, mZ + other.mZ, mW + other.mW};
        }

        constexpr Vector4 operator-(const Vector4 &other) const noexcept {
            return {mX - other.mX, mY - other.mY, mZ - other.mZ, mW - other.mW};
        }

    private:
        T mX, mY, mZ, mW;
    };

    using Vector4f = Vector4<float>;
    using Color4f = Vector4<float>;
}

#endif