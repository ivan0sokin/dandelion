#ifndef DANDELION_POLYGON_H
#define DANDELION_POLYGON_H

#include "../../core/Core.h"
#include "../../math/Vector3.h"

#include <memory>
#include <array>

namespace Dandelion {

    class DANDELION_API Polygon {
    public:
        Polygon() noexcept = delete;

        virtual ~Polygon() noexcept = default;

        static std::shared_ptr<Polygon> Create(const std::array<Vector3f, 3> &positions, const std::array<Color3f, 3> &colors) noexcept;

    protected:
        constexpr Polygon(const std::array<Vector3f, 3> &positions, const std::array<Color3f, 3> &colors) noexcept : mPositions(positions), mColors(colors) {}

    protected:
        std::array<Vector3f, 3> mPositions;
        std::array<Color3f, 3> mColors;
    };

}

#endif