#include "Application.h"
#include "WalkLayer.h"
#include "MeasureLayer.h"
#include <memory>

Application::Application() : m_Window(m_Input, *this) {
	m_LayerStack.PushLayer(std::make_unique<WalkLayer>(m_Input));
    m_LayerStack.PushLayer(std::make_unique<MeasureLayer>(m_Input));
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
    auto& layers = m_LayerStack.GetLayers();
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        (*it)->OnKey(key, action);
    }
}


void Application::OnMouseMove(double x, double y) {
    auto& layers = m_LayerStack.GetLayers();
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        (*it)->OnMouseMove(x, y);
    }
}

void Application::OnMouseButton(int button, int action) {
    auto& layers = m_LayerStack.GetLayers();
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        (*it)->OnMouseButton(button, action, m_Input.GetMouseX(), m_Input.GetMouseY());
    }
}