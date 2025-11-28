#include "WalkLayer.h"
#include "GLFW/glfw3.h"

WalkLayer::WalkLayer(Input& input) 
    : m_Input(input) {}

void WalkLayer::OnUpdate(float dt) {
    if (m_Input.IsKeyPressed(GLFW_KEY_W)) m_Mode.Update(dt, WalkMode::MoveDirection::UP);
    if (m_Input.IsKeyPressed(GLFW_KEY_S)) m_Mode.Update(dt, WalkMode::MoveDirection::DOWN);
    if (m_Input.IsKeyPressed(GLFW_KEY_A)) m_Mode.Update(dt, WalkMode::MoveDirection::LEFT);
    if (m_Input.IsKeyPressed(GLFW_KEY_D)) m_Mode.Update(dt, WalkMode::MoveDirection::RIGHT);
}

void WalkLayer::OnKey(int key, int action) {
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        m_RequestModeSwitch = true;
    }
}
