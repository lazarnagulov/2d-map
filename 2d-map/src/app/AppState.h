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

    inline WalkMode& GetWalkMode() { return m_WalkMode; }
    inline MeasureMode& GetMeasureMode() { return m_MeasureMode; }

    inline const WalkMode& GetWalkMode() const { return m_WalkMode; }
    inline const MeasureMode& GetMeasureMode() const { return m_MeasureMode; }

private:
    Mode m_CurrentMode;
    WalkMode m_WalkMode;
    MeasureMode m_MeasureMode;
};