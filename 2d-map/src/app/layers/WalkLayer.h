#pragma once

#include "../../core/Layer.h"
#include "../../core/Input.h"
#include "../../core/Texture.h"
#include "../../core/Renderer2D.h"
#include "../../core/Camera.h"
#include "../states/WalkState.h"

class WalkLayer : public Layer {
public:
    WalkLayer(Input& input, Camera& camera);
    void OnUpdate(float dt) override; 
    void OnRender(Renderer2D& renderer) override;
    void OnKey(int key, int action) override;
    void OnAttach() override;

    inline WalkState& GetState() { return m_State;  }
private:
    void UpdateCameraZoom(float dt);
private:
    Input& m_Input;
    WalkState m_State;
    Camera& m_Camera;
    Texture m_MapPinTexture;

    float m_ZoomSpeed = 0.5f;
    float m_MinZoom = 1.0f;
    float m_MaxZoom = 2.5f; 
    static constexpr float INITIAL_ZOOM = 1.5f; 
};