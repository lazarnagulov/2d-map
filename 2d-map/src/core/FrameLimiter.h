#pragma once

#include <GLFW/glfw3.h>

class FrameLimiter {
public:
    FrameLimiter(int targetFps);

    bool ShouldRender();
    double GetDeltaTime() const { return m_DeltaTime; }

private:
    double m_TargetFrameTime;
    double m_LastFrameTime;
    double m_DeltaTime;
};
