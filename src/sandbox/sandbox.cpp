#include <Dandelion.h>
#include <GL/gl.h>

using namespace Dandelion;

class SandboxApplication : public Application {
public:
    SandboxApplication() noexcept = default;

    ~SandboxApplication() override = default;

    void Run() noexcept override {
        this->SetUpLogger();

        MainWindow::SetInitialParameters(WindowParameters("Sandbox", 1280, 720));
        MainWindow::Instance()->Create();
        MainWindow::Instance()->MakeContextCurrent();
        MainWindow::Instance()->Show();

        double totalTime = 0.0;
        unsigned long long frameCount = 0;

        Timer<double> timer;
        while (!MainWindow::Instance()->ShouldBeClosed()) {
            this->Draw();

            ++frameCount;
            timer.Update();
            totalTime += timer.Elapsed();

            MainWindow::Instance()->SwapBuffers();
            MainWindow::Instance()->PollEvents();
        }

        MainWindow::Instance()->Destroy();

        mLogger->Log(LogLevel::Info, "Average FPS: " + std::to_string(1000.0 * static_cast<double>(frameCount) / totalTime));
    }

private:
    void SetUpLogger() noexcept {
        mLogger = std::make_unique<Logger>("Sandbox", "Sandbox.log");
        mLogger->Register();
        mLogger->Log(LogLevel::Info, "Hello, Sandbox!");
    }

    void Draw() noexcept {
        glBegin(GL_TRIANGLES);

        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-0.35, -0.5);

        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(0.35, -0.5);

        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(0.0, 0.5);

        glEnd();
    }

private:
    std::unique_ptr<Logger> mLogger;
};

Application* CreateApplication() {
    return new SandboxApplication();
}