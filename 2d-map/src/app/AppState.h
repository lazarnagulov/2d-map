#pragma once
#include "WalkMode.h"
#include "MeasureMode.h"

class AppState {
public:
    enum class Mode {
        WALK,
        MEASURE
    };

    AppState();

    void SwitchMode();
    inline Mode GetCurrentMode() const { return m_CurrentMode; }

private:
    Mode m_CurrentMode;
};