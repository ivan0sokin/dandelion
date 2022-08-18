#ifndef DANDELION_GLPOLYGON_H
#define DANDELION_GLPOLYGON_H

#include "../../objects/Polygon.h"

namespace Dandelion {

    class DANDELION_API GLPolygon : Polygon {
    public:
        GLPolygon() noexcept = delete;

        constexpr GLPolygon(const std::array<Vector3f, 3> &positions, const std::array<Color3f, 3> &colors) noexcept : Polygon(positions, colors) {}
    };

}

#endif