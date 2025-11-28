#pragma once

#include "../core/Input.h"
#include "../core/Layer.h"
#include "MeasureMode.h"

class MeasureLayer : public Layer {
public:
	MeasureLayer(Input& input);
	void OnMouseButton(int button, int action, double x, double y) override;
private:
	Input& m_Input;
	MeasureMode m_Mode;
};