#ifndef DANDELION_WINDOW_H
#define DANDELION_WINDOW_H

#include "Core.h"

#include <GLFW/glfw3.h>

namespace Dandelion {

    class DANDELION_API Window {
    public:
        static bool Initialize() noexcept;
        static void Terminate() noexcept;

    private:
        inline static bool isInitialized = false;
        GLFWwindow *mWindowHandle;
    };

}

#endif