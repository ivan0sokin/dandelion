#ifndef DANDELION_WINDOW_H
#define DANDELION_WINDOW_H

#include "Core.h"

#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace Dandelion {

    struct DANDELION_API WindowParameters {
        std::string title = "Dandelion";
        int width = 640, height = 480;

        WindowParameters() noexcept = default;

        inline WindowParameters(std::string_view title, int width, int height) noexcept : title(title), width(width), height(height) {}

        ~WindowParameters() noexcept = default;
    };

    class DANDELION_API Window {
    public:
        Window() noexcept = default;

        inline Window(const WindowParameters &initialParameters) noexcept : Window(initialParameters, {}) {}

        inline Window(const WindowParameters &initialParameters, std::initializer_list<std::pair<int, int>> hints) noexcept : mInitialParameters(initialParameters), mHints(hints) {}

        ~Window() noexcept = default;

        void Create() noexcept;

        void Destroy() noexcept;

        void Show() noexcept;

        void Hide() noexcept;

        void PollEvents() noexcept;

        void MakeContextCurrent() noexcept;

        void SwapBuffers() noexcept;

        bool ShouldBeClosed() noexcept;
    private:
        void SetHints() noexcept;

    private:
        GLFWwindow *mHandle;
        WindowParameters mInitialParameters;
        std::vector<std::pair<int, int>> mHints;
    };

    class DANDELION_API NonResizableWindow : public Window {
    public:
        inline NonResizableWindow(const WindowParameters &initialParameters) noexcept : Window(initialParameters, {{GLFW_RESIZABLE, GLFW_FALSE}, {GLFW_VISIBLE, GLFW_FALSE}}) {}
    };

    class DANDELION_API MainWindow : public NonResizableWindow {
    public:
        MainWindow(MainWindow &) = delete;
        MainWindow& operator=(MainWindow const&) = delete;

        static void SetInitialParameters(const WindowParameters &initialParameters) noexcept;

        static std::shared_ptr<MainWindow> Instance() noexcept;

        ~MainWindow() noexcept = default;

    private:
        inline MainWindow() noexcept : NonResizableWindow(initialParameters) {}

    private:
        static inline WindowParameters initialParameters{};
    };

}

#endif