#include <Dandelion.h>

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

        this->CreateFrameRectangle();

        auto program = mContext->CreateProgram({
            mContext->CreateFragmentShader("polygon.frag")
        });

        std::vector<Color3f> colors = {
            {1.0, 0.5, 1.0}
        };

        double totalTime = 0.0;
        unsigned long long frameCount = 0;

        program->Enable();

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

    void CreateFrameRectangle() {
        const std::vector<Vector2f> vertices = {
            {-1.0f, -1.0f},
            {1.0f, -1.0f},
            {1.0f, 1.0f},
            {-1.0f, 1.0f}
        };

        auto vertexBuffer = mContext->CreateVertexBuffer(vertices.data(), sizeof(vertices[0]) * vertices.size(), {{0, Element::Vector2f, 2 * sizeof(float), 0}});

        std::array<unsigned, 6> indices = {
            0, 1, 2,
            2, 3, 0
        };

        auto indexBuffer = mContext->CreateIndexBuffer(indices.data(), sizeof(indices));

        mTriangle = mContext->CreateRenderObject({ std::move(vertexBuffer) }, std::move(indexBuffer));
    }

    void Draw() noexcept {
        mTriangle->DrawIndexed(6);
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