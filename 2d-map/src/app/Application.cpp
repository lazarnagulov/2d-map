#include "Application.h"

#include <memory>


Application::Application() 
    : m_Input(),
    m_Window(m_Input, *this),
    m_WalkLayer(AddLayer<WalkLayer>(m_Input)),
    m_MeasureLayer(AddLayer<MeasureLayer>(m_Input)) 
{
    m_WalkLayer.SetEnabled(true);
}

Application::~Application() {
	m_Window.~Window();
}

void Application::Update(float deltaTime) {
    m_Window.Update();
    auto& layers = m_LayerStack.GetLayers();
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        (*it)->OnUpdate(deltaTime);
    }
    m_Input.EndFrame();
}

void Application::OnKey(int key, int action) {
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        m_State.SwitchMode();

        if (m_State.GetCurrentMode() == AppState::Mode::WALK) {
            m_WalkLayer.SetEnabled(true);
            m_MeasureLayer.SetEnabled(false);
        }
        else {
            m_WalkLayer.SetEnabled(false);
            m_MeasureLayer.SetEnabled(true);
        }
        return;
    }

    auto& layers = m_LayerStack.GetLayers();
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        (*it)->OnKey(key, action);
    }
}


void Application::OnMouseMove(double x, double y) {
    auto& layers = m_LayerStack.GetLayers();
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        if (!(*it)->IsEnabled())
            continue;
        (*it)->OnMouseMove(x, y);
    }
}

void Application::OnMouseButton(int button, int action) {
    auto& layers = m_LayerStack.GetLayers();
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        if (!(*it)->IsEnabled())
            continue;
        (*it)->OnMouseButton(button, action, m_Input.GetMouseX(), m_Input.GetMouseY());
    }
}

template<typename T, typename... Args>
T& Application::AddLayer(Args&&... args) {
    auto layer = std::make_unique<T>(std::forward<Args>(args)...);
    T& ref = *layer;
    m_LayerStack.PushLayer(std::move(layer));
    return ref;
}