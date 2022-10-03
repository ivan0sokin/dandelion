#ifndef DANDELION_VECTOR3_H
#define DANDELION_VECTOR3_H

#include "Vector2.h"

namespace Dandelion {

    template <typename T>
    class DANDELION_API Vector3 {
    public:
        constexpr ~Vector3() noexcept = default;

        constexpr Vector3() noexcept = default;

        constexpr Vector3(T x, T y, T z) noexcept : mX(x), mY(y), mZ(z) {}

        constexpr Vector3(T scalar) noexcept : mX(scalar), mY(scalar), mZ(scalar) {}

        constexpr Vector3(const Vector3 &begin, const Vector3 &end) noexcept : mX(end.mX - begin.mX), mY(end.mY - begin.mY), mZ(end.mZ - begin.mZ) {}

        constexpr Vector3(const Vector2<T> &other, T z) noexcept : mX(other.mX), mY(other.mY), mZ(z) {}

        constexpr Vector3(T x, const Vector2<T> &other) noexcept : mX(x), mY(other.mX), mZ(other.mY) {}

        constexpr T DotProduct(const Vector3 &other) const noexcept { return mX * other.mX + mY * other.mY + mZ * other.mZ; }

        constexpr Vector3 CrossProduct(const Vector3 &other) const noexcept {
            return {
                mY * other.z - other.y * mZ,
                mZ * other.mX - other.mZ * mX,
                mX * other.mY - other.mX * mY
            };
        }

        constexpr T SquaredMagnitude() const noexcept { return mX * mX + mY * mY + mZ * mZ; }

        constexpr T Magnitude() const noexcept { return std::sqrt(this->SquaredMagnitude()); }

        constexpr Vector3 Normalize() const noexcept {
            return *this / this->Magnitude();
        }

        constexpr Vector3 operator+(T scalar) const noexcept {
            return {mX + scalar, mY + scalar, mZ + scalar};
        }

        constexpr Vector3 operator-(T scalar) const noexcept {
            return {mX - scalar, mY - scalar, mZ - scalar};
        }

        constexpr Vector3 operator*(T scalar) const noexcept {
            return {mX * scalar, mY * scalar, mZ * scalar};
        }

        constexpr Vector3 operator/(T scalar) const noexcept {
            return *this * (1 / scalar);
        }

        constexpr Vector3 operator+(const Vector3 &other) const noexcept {
            return {mX + other.mX, mY + other.mY, mZ + other.mZ};
        }

        constexpr Vector3 operator-(const Vector3 &other) const noexcept {
            return {mX - other.mX, mY - other.mY, mZ - other.mZ};
        }

    private:
        T mX, mY, mZ;
    };

    using Vector3f = Vector3<float>;
    using Color3f = Vector3<float>;
}

#endif