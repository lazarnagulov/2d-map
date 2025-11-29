#pragma once

#include "../../core/Layer.h"
#include "../../core/Input.h"

class CompassCursorLayer : public Layer {
public:
    CompassCursorLayer(Input& input, const glm::vec2& target);

    void OnRender(Renderer2D& renderer) override;
    void OnUpdate(float dt) override {}

private:
    Input& m_Input;
    Texture m_CompassBase;
    glm::vec2 m_Target;
};
