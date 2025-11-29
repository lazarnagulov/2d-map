#include "Application.h"
#include "../core/FrameLimiter.h"
#include "./layers/ModeLayer.h"

#include <memory>


Application::Application()
    : m_Input(),
    m_Window(m_Input, *this),
    m_WalkLayer(AddLayer<WalkLayer>(m_Input, m_Camera)),
    m_MeasureLayer(AddLayer<MeasureLayer>(m_Input)),
    m_ModeLayer(AddLayer<ModeLayer>(m_State)),
    m_Camera({ 0,0 }, 1.0f)
{
    InitRenderer();
    m_BackgroundTexture = std::make_unique<Texture>("./src/assets/textures/map.jpg");
    m_MeasureLayer.SetTextPosition({ 50.0f, m_Window.GetHeight() - 50.0f });


    m_State.SetOnModeChanged([this](AppState::Mode mode) {
        SyncLayersWithState();
        if (mode == AppState::Mode::MEASURE) {
            m_Camera.SetZoom(1.0f);
            m_Camera.SetPosition({ 0.0f,0.0f });
        }
        else {
            m_Camera.SetZoom(1.5f);
            m_Camera.SetPosition(m_WalkLayer.GetState().GetPosition());
        }
    });

    SyncLayersWithState();
}

Application::~Application() = default;


void Application::Run(float targetFps) {

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

    m_TextShader = std::make_shared<Shader>(
        "./src/assets/shaders/text.vert",
        "./src/assets/shaders/text.frag"
    );

    m_Renderer = std::make_unique<Renderer2D>(m_QuadShader);
    m_Renderer->SetTextShader(m_TextShader);
    m_Renderer->LoadFont("./src/assets/fonts/Vaseline Extra.ttf");
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

    m_Renderer->BeginScene(m_Camera.GetViewProjection(width, height));

    m_Renderer->DrawQuad(
        { 0.0f, 0.0f },
        { static_cast<float>(m_BackgroundTexture->GetWidth()),
          static_cast<float>(m_BackgroundTexture->GetHeight()) },
        *m_BackgroundTexture
    );

    DispatchToLayers([&](Layer& layer) {
        if (&layer != &m_ModeLayer && &layer != &m_MeasureLayer)
            layer.OnRender(*m_Renderer);
    });

    m_Renderer->EndScene();

    glm::mat4 screenOrtho = glm::ortho(
        0.0f, static_cast<float>(width),
        0.0f, static_cast<float>(height),
        -1.0f, 1.0f
    );

    m_Renderer->BeginScene(screenOrtho);
    
    m_Renderer->DrawText("Lazar Nagulov SV61/2022", { 50.0f, m_Window.GetHeight() - 100.0f }, 1.0f, { 0.0f, 0.8f, 1.0f, 1.0f });
    
    if(m_WalkLayer.IsEnabled())
        m_Renderer->DrawText(
            "Total distance: " + std::to_string(m_WalkLayer.GetState().GetWalkedDistance()),
            { 50.0f, m_Window.GetHeight() - 50.0f },
            0.5f,
            { 0.0f, 0.0f, 0.0f, 1.0f }
        );

    DispatchToLayers([&](Layer& layer) {
        if (&layer != &m_WalkLayer)
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