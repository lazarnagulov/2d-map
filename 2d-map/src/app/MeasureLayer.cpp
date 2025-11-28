#include "MeasureLayer.h"
#include "GLFW/glfw3.h"

MeasureLayer::MeasureLayer(Input& input) : m_Input(input) {}

void MeasureLayer::OnMouseButton(int button, int action, double x, double y) {
    glm::vec2 point = { static_cast<float>(x), static_cast<float>(y) };

    if (action != GLFW_PRESS)
        return; 

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        int pos = m_Mode.FindPointNear(point);
        if (pos < 0)
            m_Mode.AddPoint(point);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        int pos = m_Mode.FindPointNear(point);
        if (pos >= 0)
            m_Mode.RemovePoint(pos);
    }
}
