#include "Input.h"
#include <GLFW/glfw3.h>

void Input::OnKeyEvent(int key, int action) {
    if (action == GLFW_PRESS) {
        m_KeysPressed[key] = true;
    }
}
void Input::OnMouseButtonEvent(int button, int action) {
    if (action == GLFW_PRESS)
        m_MouseButtons[button] = true;
    else if (action == GLFW_RELEASE)
        m_MouseButtons[button] = false;
}

void Input::OnMouseMove(double x, double y) {
    m_MouseX = x;
    m_MouseY = y;
}

void Input::EndFrame() {
    m_KeysPressed.reset();
}

