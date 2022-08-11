#include <Dandelion.h>
#include <GL/gl.h>

using namespace Dandelion;

class SandboxApplication : public Application {
public:
    SandboxApplication() noexcept = default;

    ~SandboxApplication() override = default;

    void Run() noexcept override {
        mLogger = std::make_unique<Logger>("Sandbox", "Sandbox.log");
        mLogger->Register();
        mLogger->Log(LogLevel::Info, "Hello, Sandbox!");

        auto wnd = NonResizableWindow("Dandelion", 1280, 720);
        wnd.Create();
        wnd.MakeContextCurrent();
        while (!wnd.ShouldBeClosed()) {
            glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(-0.35, -0.5);

            glColor3f(0.0, 1.0, 0.0);
            glVertex2f(0.35, -0.5);

            glColor3f(0.0, 0.0, 1.0);
            glVertex2f(0.0, 0.5);
            glEnd();

            wnd.SwapBuffers();

            wnd.PollEvents();
        }
    }

private:
    std::unique_ptr<Logger> mLogger;
};

Application* CreateApplication() {
    return new SandboxApplication();
}