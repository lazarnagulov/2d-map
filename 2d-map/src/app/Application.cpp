#include "Application.h"
#include "../core/FrameLimiter.h"
#include "./layers/ModeLayer.h"

#include <memory>


Application::Application() 
    : m_Input(),
      m_Window(m_Input, *this),
      m_WalkLayer(AddLayer<WalkLayer>(m_Input)),
      m_MeasureLayer(AddLayer<MeasureLayer>(m_Input)),
      m_ModeLayer(AddLayer<ModeLayer>(m_State))
{
    InitRenderer();
    m_BackgroundTexture = std::make_unique<Texture>("./src/assets/textures/map.jpg");

    m_State.SetOnModeChanged([this](AppState::Mode mode) {
        SyncLayersWithState();
    });

    SyncLayersWithState();
}

Application::~Application() = default;


void Application::Run(float targetFps) {
    auto quadShader = std::make_shared<Shader>("./src/assets/shaders/quad.vert", "./src/assets/shaders/quad.frag");
    Renderer2D renderer(quadShader);

    FrameLimiter frameLimiter(targetFps);
    while (!GetWindow().ShouldClose()) {
        if (frameLimiter.ShouldRender()) {
            Render();
            Update(frameLimiter.GetDeltaTime());
        }
    }
}

void Application::InitRenderer() {
    m_QuadShader = std::make_shared<Shader>(
        "./src/assets/shaders/quad.vert",
        "./src/assets/shaders/quad.frag"
    );

    m_Renderer = std::make_unique<Renderer2D>(m_QuadShader);
    UpdateProjection();
}

void Application::UpdateProjection() {
    int width = m_Window.GetWidth();
    int height = m_Window.GetHeight();

    m_Projection = glm::ortho(
        0.0f, static_cast<float>(width),
        0.0f, static_cast<float>(height),
        -1.0f, 1.0f
    );
}

void Application::Update(float deltaTime) {
    m_Window.Update();

    DispatchToLayers([&](Layer& layer) {
        layer.OnUpdate(deltaTime);
    });

    m_Input.EndFrame();
}

void Application::SyncLayersWithState() {
    bool isWalkMode = (m_State.GetCurrentMode() == AppState::Mode::WALK);

    m_WalkLayer.SetEnabled(isWalkMode);
    m_MeasureLayer.SetEnabled(!isWalkMode);
    m_ModeLayer.SetEnabled(true); 
}

void Application::Render() {
    int width = m_Window.GetWidth();
    int height = m_Window.GetHeight();

    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width, height);

    LoadMode();
    m_Renderer->BeginScene(m_Projection);

    m_Renderer->DrawQuad(
        { width / 2, height / 2 }, 
        { m_BackgroundTexture->GetWidth(), m_BackgroundTexture->GetHeight() }, 
        *m_BackgroundTexture
    );

    DispatchToLayers([&](Layer& layer) {
        layer.OnRender(*m_Renderer);
    });

    m_Renderer->EndScene();
}

void Application::OnKey(int key, int action) {
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        m_State.SwitchMode();
        return;
    }

    DispatchToLayers([&](Layer& layer) {
        layer.OnKey(key, action);
    });
}

void Application::LoadMode() {
    if (m_State.GetCurrentMode() == AppState::Mode::WALK) {
        m_WalkLayer.SetEnabled(true);
        m_MeasureLayer.SetEnabled(false);
    }
    else {
        m_WalkLayer.SetEnabled(false);
        m_MeasureLayer.SetEnabled(true);
    }
}

void Application::OnMouseMove(double x, double y) {
    DispatchToLayers([&](Layer& layer) {
        layer.OnMouseMove(x, y);
    });
}

void Application::OnMouseButton(int button, int action) {
    double x = m_Input.GetMouseX();
    double y = m_Window.GetHeight() - m_Input.GetMouseY();

    DispatchToLayers([&](Layer& layer) {
        layer.OnMouseButton(button, action, x, y);
    });
}

template<typename T, typename... Args>
T& Application::AddLayer(Args&&... args) {
    auto layer = std::make_unique<T>(std::forward<Args>(args)...);
    T& ref = *layer;
    m_LayerStack.PushLayer(std::move(layer));
    return ref;
}

template<typename Event>
void Application::DispatchToLayers(Event&& eventCallback) {
    auto& layers = m_LayerStack.GetLayers();
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        if (!(*it)->IsEnabled())
            continue;
        eventCallback(**it);
    }
}