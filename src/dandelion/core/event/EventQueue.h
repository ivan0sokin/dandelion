#ifndef DANDELION_EVENTQUEUE_H
#define DANDELION_EVENTQUEUE_H

#include "../Core.h"
#include "../Logger.h"
#include "Event.h"

#include <deque>

namespace Dandelion {

    class DANDELION_API EventQueue {
    public:
        EventQueue() noexcept = default;

        virtual ~EventQueue() noexcept = default;

        inline const Event & Next() noexcept {
            if (this->IsEmpty()) {
                CoreLogger::Instance()->Log(LogLevel::Error, "Event queue is empty");
                return mNullEvent;
            }

            return *mBuffer[mIndex++].get();
        }

        inline bool IsEmpty() const noexcept {
            return mIndex >= mBuffer.size();
        }

    protected:
        std::deque<std::unique_ptr<Event>> mBuffer;
        std::size_t mIndex = 0;
        NullEvent mNullEvent;
    };

    class DANDELION_API EditableEventQueue : public EventQueue {
    public:
        EditableEventQueue() noexcept = default;

        ~EditableEventQueue() noexcept override = default;

        template<typename T, typename ...Args>
        inline void Push(Args &&...args) noexcept {
            mBuffer.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        }

        inline void ClearHandled() noexcept {
            while (mIndex > 0) {
                mBuffer.pop_front();
                --mIndex;
            }
        }
    };
}

#endif