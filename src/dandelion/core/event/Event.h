#ifndef DANDELION_EVENT_H
#define DANDELION_EVENT_H

#include "../Core.h"

namespace Dandelion {

    class DANDELION_API Event {
    public:
        enum class Type : unsigned {
            Null = 0,
            NonNull
        };

    public:
        constexpr Event(const Type &type) noexcept : mType(type) {}

        virtual ~Event() noexcept = default;

        constexpr bool IsNull() const noexcept { return mType == Type::Null; }

        template<typename T>
        constexpr T As() const noexcept { return *static_cast<const T*>(this); }

    private:
        Type mType;
    };

    class DANDELION_API NullEvent : public Event {
    public:
        constexpr NullEvent() noexcept : Event(Event::Type::Null) {}

        ~NullEvent() noexcept override = default;
    };

    class DANDELION_API NonNullEvent : public Event {
    public:
        constexpr NonNullEvent() noexcept : Event(Event::Type::NonNull) {}

        ~NonNullEvent() noexcept override = default;
    };

}

#endif