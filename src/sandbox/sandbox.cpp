#include <Dandelion.h>

using namespace Dandelion;

class SandboxApplication : public Application {
public:
    SandboxApplication() noexcept = default;

    ~SandboxApplication() override = default;

    void Run() noexcept override {
        mLogger = std::make_unique<Logger>("Sandbox", "Sandbox.log");
        mLogger->Create();
        mLogger->Log(LogLevel::Info, "Hello, Sandbox!");

        auto wnd = NonResizableWindow("Dandelion", 1280, 720);
        wnd.Create();

        while (true) {
            wnd.PollEvents();
        }
    }

private:
    std::unique_ptr<Logger> mLogger;
};

Application* CreateApplication() {
    return new SandboxApplication();
}