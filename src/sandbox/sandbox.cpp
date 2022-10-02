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
        MainWindow::Instance()->Show();

        mContext = Engine::Instance()->CreateContext(MainWindow::Instance());
        mContext->Initialize();

        this->CreateTriangle();

        auto program = mContext->CreateProgram({
            mContext->CreateVertexShader("polygon.vert"),
            mContext->CreateFragmentShader("polygon.frag")
        });

        program->Enable();

        double totalTime = 0.0;
        unsigned long long frameCount = 0;

        Timer timer;
        while (!MainWindow::Instance()->ShouldBeClosed()) {
            this->Draw();

            ++frameCount;
            timer.Update();
            totalTime += timer.Elapsed();

            if (totalTime > 2000.0) {
                mLogger->Log(LogLevel::Info, "FPS: " + std::to_string(1000.0 * static_cast<double>(frameCount) / totalTime));
                frameCount = 0;
                totalTime = 0.0;
            }

            MainWindow::Instance()->SwapBuffers();
            MainWindow::Instance()->PollEvents();
        }

        mContext->Destroy();
        MainWindow::Instance()->Destroy();
    }

private:
    void SetUpLogger() noexcept {
        mLogger = std::make_unique<Logger>("Sandbox", "Sandbox.log");
        mLogger->Register();
        mLogger->Log(LogLevel::Info, "Hello, Sandbox!");
    }

    void CreateTriangle() {
        std::array<float, 15> vertices = {
            -0.35, -0.5, 1.0, 0.0, 0.0,
            0.35, -0.5, 0.0, 1.0, 0.0,
            0.0, 0.5, 0.0, 0.0, 1.0
        };

        Layout layout = {
            {0, Element::Vector2f, 5 * sizeof(float), 0},
            {1, Element::Vector3f, 5 * sizeof(float), 2 * sizeof(float)}
        };

        auto vertexBuffer = mContext->CreateVertexBuffer(vertices.data(), sizeof(vertices), layout);

        mTriangle = mContext->CreateRenderObject({ std::move(vertexBuffer) }, {});
    }

    void Draw() noexcept {
        mTriangle->Draw(3);
    }

private:
    std::unique_ptr<Logger> mLogger;
    std::shared_ptr<Context> mContext;
    std::shared_ptr<RenderObject> mTriangle;
    std::shared_ptr<Program> mProgram;
};

Application* CreateApplication() {
    return new SandboxApplication();
}