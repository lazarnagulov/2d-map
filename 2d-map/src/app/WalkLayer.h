#pragma once

#include "../core/Layer.h"
#include "../core/Input.h"
#include "../core/Texture.h"
#include "WalkMode.h"

class WalkLayer : public Layer {
public:
    WalkLayer(Input& input);
    void OnUpdate(float dt) override; 
    void OnKey(int key, int action) override;
private:
    Input& m_Input;
    WalkMode m_Mode;
    bool m_RequestModeSwitch = false;
    bool m_Active = true;
};