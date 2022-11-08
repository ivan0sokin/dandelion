#include "Mouse.h"

namespace Dandelion {

    Mouse::Mouse() noexcept {
        mEventQueue = std::make_shared<EditableEventQueue>();
    }

    std::shared_ptr<Mouse> Mouse::Instance() noexcept {
        static std::shared_ptr<Mouse> instance{new Mouse};
        return instance;
    }

}