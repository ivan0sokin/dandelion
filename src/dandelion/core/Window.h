#ifndef DANDELION_WINDOW_H
#define DANDELION_WINDOW_H

#include "Core.h"

#include <GLFW/glfw3.h>

#include <string>
#include <string_view>
#include <vector>

namespace Dandelion {

    class DANDELION_API Window {
    public:
        Window() noexcept = default;

        inline Window(std::string_view title, int width, int height) noexcept : Window(title, width, height, {}) {}

        inline Window(std::string_view title, int width, int height, std::initializer_list<std::pair<int, int>> hints) noexcept : mTitle(title), mWidth(width), mHeight(height), mHints(hints) {}

        ~Window() noexcept;

        void Create() noexcept;

        void PollEvents() noexcept;

        void MakeCurrent() noexcept;

    private:
        void SetHints() noexcept;

    private:
        GLFWwindow *mHandle;
        std::string mTitle;
        int mWidth, mHeight;
        std::vector<std::pair<int, int>> mHints;
    };

    class DANDELION_API NonResizableWindow : public Window {
    public:
        inline NonResizableWindow(std::string_view title, int width, int height) noexcept : Window(title, width, height, {{GLFW_RESIZABLE, GLFW_FALSE}}) {}
    };
}

#endif