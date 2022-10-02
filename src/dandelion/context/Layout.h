#ifndef DANDELION_LAYOUT_H
#define DANDELION_LAYOUT_H

#include "../core/Core.h"

#include <vector>
#include <array>

namespace Dandelion {

    enum class Element : std::size_t {
        Float = 0,
        Vector2f,
        Vector3f,
        Vector4f
    };

    class DANDELION_API Layout {
    public:
        Layout() noexcept = default;

        inline Layout(std::initializer_list<std::tuple<std::size_t, Element, std::size_t, std::size_t>> elements) noexcept : mElements(elements) {}

        auto begin() noexcept { return mElements.begin(); }

        auto end() noexcept { return mElements.end(); }

        static inline std::size_t ComponentCount(const Element &element) noexcept { return componentCount[static_cast<std::size_t>(element)]; }

        static inline Element ComponentType(const Element &element) noexcept { return componentType[static_cast<std::size_t>(element)]; }
    private:
        std::vector<std::tuple<std::size_t, Element, std::size_t, std::size_t>> mElements;

        static constexpr std::array<std::size_t, 4> componentCount = { 1, 2, 3, 4 };
        static constexpr std::array<Element, 4> componentType = {Element::Float, Element::Float, Element::Float, Element::Float };
    };

}

#endif