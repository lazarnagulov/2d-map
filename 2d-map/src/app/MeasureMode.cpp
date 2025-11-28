#include "MeasureMode.h"

void MeasureMode::AddPoint(const glm::vec2& point) {
	m_Points.push_back(point);
	RecalculateDistance();
}
void MeasureMode::RemovePoint(size_t index) {
	if (index < m_Points.size()) {
		m_Points.erase(m_Points.begin() + index);
		RecalculateDistance();
	}
}
void MeasureMode::Clear() {
	m_Points.clear();
	m_TotalDistance = 0.0f;
}

int MeasureMode::FindPointNear(const glm::vec2& pos, float threshold /* = 10.0f */) const {
	for (size_t i = 0; i < m_Points.size(); ++i) {
		float dist = glm::distance(m_Points[i], pos);
		if (dist <= threshold) {
			return static_cast<int>(i);
		}
	}
	return -1;
}

void MeasureMode::RecalculateDistance() {
	m_TotalDistance = 0.0f;

	for (size_t i = 1; i < m_Points.size(); ++i) {
		m_TotalDistance += glm::distance(m_Points[i - 1], m_Points[i]);
	}
}
