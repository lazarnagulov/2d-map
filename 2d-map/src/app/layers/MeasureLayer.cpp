#include "MeasureLayer.h"
#include "GLFW/glfw3.h"
#include <iostream>

MeasureLayer::MeasureLayer(Input& input) : m_Input(input) {}

MeasureLayer::~MeasureLayer() {
}

void MeasureLayer::OnMouseButton(int button, int action, double x, double y) {
    glm::vec2 point = { static_cast<float>(x), static_cast<float>(y) };

    if (action != GLFW_PRESS)
        return; 

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        int pos = m_State.FindPointNear(point);
        if (pos < 0)
            m_State.AddPoint(point);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        int pos = m_State.FindPointNear(point);
        if (pos >= 0)
            m_State.RemovePoint(pos);
    }
}

void MeasureLayer::OnRender(Renderer2D& renderer) {
    const auto& points = m_State.GetPoints();
    const float thickness = 5.0f;
    
    for (size_t i = 0; i < points.size(); i++) {
        const glm::vec2& p = points[i];

        renderer.DrawCircle(p, 10.0f, { 1,1,1,1 }, true);

        if (i > 0)
            DrawLine(renderer, points[i - 1], points[i]);
    }
}

void MeasureLayer::DrawLine(Renderer2D& renderer, const glm::vec2& p0, const glm::vec2& p1) {
    glm::vec2 dir = p1 - p0;
    float len = glm::length(dir);

    if (len > 0.001f) {
        glm::vec2 n = dir / len;

        renderer.DrawLine(
            p0 + n * CIRCLE_RADIUS, 
            p1 - n * CIRCLE_RADIUS, 
            LINE_THICKNESS, 
            { 1.0f, 0.5f, 0.0f, 1.0f }
        );
    }
}