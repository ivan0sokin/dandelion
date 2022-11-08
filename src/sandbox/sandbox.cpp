#include <Dandelion.h>
#include <core/input/Mouse.h>
#include <core/input/MouseEvent.h>

using namespace Dandelion;

class SandboxApplication : public Application {
public:
    SandboxApplication() noexcept = default;

    ~SandboxApplication() override = default;

    void Run() noexcept override {
        this->SetUpLogger();

        MainWindow::Instance()->SetInitialParameters(WindowParameters("Sandbox", 1920, 1080));
        MainWindow::Instance()->Create();
        MainWindow::Instance()->Show();

        mContext = Engine::Instance()->CreateContext(MainWindow::Instance());
        mContext->Initialize();

        this->CreateFrameRectangle();

        auto program = mContext->CreateProgram({
            mContext->CreateFragmentShader("fragment.glsl")
        });

        program->Enable();

        this->CreateUniformBuffer();

        while (!MainWindow::Instance()->ShouldBeClosed()) {
            this->UpdateFPSCounter();
            if (mFrameTime > resetFrameTimeInMilliseconds) {
                this->PrintFPS();
            }

            MainWindow::Instance()->PollEvents();
            this->UpdateUniformBuffer();

            this->Draw();
            MainWindow::Instance()->SwapBuffers();
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

    void UpdateFPSCounter() {
        ++mFrameCount;
        mTimer.Update();
        mFrameTime += mTimer.Elapsed();
    }

    void PrintFPS() {
        mLogger->Log(LogLevel::Info, "FPS: " + std::to_string(1000.0 * static_cast<double>(mFrameCount) / mFrameTime));
        mFrameCount = 0;
        mFrameTime = 0.0;
    }

    void CreateUniformBuffer() noexcept {
        mUniformBuffer = mContext->CreateUniformBuffer(mUniformBufferData.data(), mUniformBufferData.size() * sizeof(mUniformBufferData[0]), uniformBufferBindingLocation);
    }

    void UpdateUniformBuffer() {
        auto mouseEventQueue = Mouse::Instance()->EventQueue();

        while (!mouseEventQueue->IsEmpty()) {
            const auto &e = mouseEventQueue->Next();
            if (e.IsNull()) {
                break;
            }

            auto type = e.As<MouseEvent>().GetType();
            if (type == MouseEvent::Type::Move) {
                auto move = e.As<MouseMoveEvent>();

                mUniformBufferData[2] = (float)move.x;
                mUniformBufferData[3] = (float)move.y;

                mUniformBuffer->SetSubData(mUniformBufferData.data() + 2, 2 * uniformBufferElementSize, 2 * uniformBufferElementSize);
            } else if (type == MouseEvent::Type::Scroll) {
                auto scroll = e.As<MouseScrollEvent>();

                mUniformBufferData[4] += std::signbit(scroll.yOffset) ? -1.0 : 1.0;
                this->ValidateScale();

                mLogger->Log(LogLevel::Info, "Scale is " + std::to_string(mUniformBufferData[4]));

                mUniformBufferData[5] = this->FindGridScaleFactor();

                mUniformBuffer->SetSubData(mUniformBufferData.data() + 4, 4 * uniformBufferElementSize, 2 * uniformBufferElementSize);
            }
        }
    }

    void ValidateScale() noexcept {
        mUniformBufferData[4] = std::max(std::min(mUniformBufferData[4], maxScale), minScale);
    }

    constexpr float FindGridScaleFactor() const noexcept {
        using namespace std::ranges;
        return gridScaleFactors[distance(scales.cbegin(), lower_bound(std::as_const(scales), mUniformBufferData[4]))];
    }

    void Draw() noexcept {
        mTriangle->DrawIndexed(6);
    }

private:
    std::unique_ptr<Logger> mLogger;
    std::shared_ptr<Context> mContext;
    std::shared_ptr<RenderObject> mTriangle;
    std::shared_ptr<Program> mProgram;

    std::shared_ptr<UniformBuffer> mUniformBuffer;
    std::array<float, 6> mUniformBufferData = {1920.0, 1080.0, 0.0, 0.0, 50.0, 1.0};

    Timer mTimer;
    double mFrameTime = 0.0;
    unsigned long long mFrameCount = 0;

private:
    constexpr static size_t uniformBufferBindingLocation = 0;
    constexpr static size_t uniformBufferElementSize = sizeof(mUniformBufferData[0]);

    constexpr static double resetFrameTimeInMilliseconds = 2000.0;

    constexpr static float minScale = 1.0, maxScale = 100.0;
    constexpr static std::size_t numScales = 12;
    constexpr static std::array<float, numScales> scales = {1.0, 2.0, 5.0, 10.0, 20.0, 59.0, 69.0, 80.0, 85.0, 92.0, 95.0, 100.0};
    constexpr static std::array<float, numScales> gridScaleFactors = {1.0 / 32.0, 1.0 / 16.0, 1.0 / 8.0, 1.0 / 4.0, 1.0 / 2.0, 1.0, 1.5, 2.0, 2.1, 2.2, 2.4, 2.5};
};

Application* CreateApplication() {
    return new SandboxApplication();
}