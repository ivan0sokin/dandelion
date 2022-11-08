#ifndef DANDELION_MOUSEEVENT_H
#define DANDELION_MOUSEEVENT_H

#include "../event/Event.h"

namespace Dandelion {

    class DANDELION_API MouseEvent : public NonNullEvent {
    public:
        enum class Type : unsigned {
            Move = 0,
            Scroll
        };

    public:
        constexpr MouseEvent(const Type &type) noexcept : mType(type) {}

        ~MouseEvent() noexcept override = default;

        constexpr Type GetType() const noexcept { return mType; }

    private:
        Type mType;
    };

    class DANDELION_API MouseMoveEvent : public MouseEvent {
    public:
        constexpr MouseMoveEvent(double x, double y) noexcept : MouseEvent(MouseEvent::Type::Move), x(x), y(y) {}

        ~MouseMoveEvent() noexcept override = default;

    public:
        double x, y;
    };

    class DANDELION_API MouseScrollEvent : public MouseEvent {
    public:
        constexpr MouseScrollEvent(double xOffset, double yOffset) noexcept : MouseEvent(MouseEvent::Type::Scroll), xOffset(xOffset), yOffset(yOffset) {}

        ~MouseScrollEvent() noexcept override = default;

    public:
        double xOffset, yOffset;
    };

}

#endif