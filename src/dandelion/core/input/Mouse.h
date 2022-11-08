#ifndef DANDELION_MOUSE_H
#define DANDELION_MOUSE_H

#include "../Core.h"
#include "../event/EventQueue.h"

#include <memory>

namespace Dandelion {

    class DANDELION_API Mouse {
        friend class Window;
    public:
        Mouse(Mouse &) = delete;
        Mouse& operator=(Mouse const&) = delete;

        static std::shared_ptr<Mouse> Instance() noexcept;

        ~Mouse() noexcept = default;

        inline std::shared_ptr<EventQueue> EventQueue() noexcept { return mEventQueue; }

    private:
        Mouse() noexcept;

    private:
        std::shared_ptr<EditableEventQueue> mEventQueue;
    };

}

#endif