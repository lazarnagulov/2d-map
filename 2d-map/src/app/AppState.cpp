#include "AppState.h"

AppState::AppState()
	: m_CurrentMode(Mode::WALK) {}

void AppState::SwitchMode() {
	m_CurrentMode = (m_CurrentMode == Mode::WALK) ? Mode::MEASURE : Mode::WALK;
}