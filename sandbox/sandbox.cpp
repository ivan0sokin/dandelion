#include <Dandelion.h>
#include <iostream>

class SandboxApplication : public Dandelion::Application {
public:
    SandboxApplication() noexcept = default;

    ~SandboxApplication() override = default;

    void Run() noexcept override {
        std::cout << "Hello, Dandelion!";
    }
};

Dandelion::Application* CreateApplication() {
    return new SandboxApplication();
}