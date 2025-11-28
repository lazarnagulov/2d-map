#pragma once

#include "AppState.h"
#include "MeasureLayer.h"
#include "WalkLayer.h"
#include "../core/Window.h"
#include "../core/LayerStack.h"

class Application : public IEventListener {
public:
	Application();
	~Application();

	void Update(float deltaTime);
	void OnKey(int key, int action) override;
	void OnMouseMove(double x, double y) override;
	void OnMouseButton(int button, int action) override;

	inline const Window& GetWindow() const { return m_Window; }
	inline Window& GetWindow() { return m_Window; }

	template<typename T, typename... Args>
	T& AddLayer(Args&&... args);

private:
	Input m_Input;
	Window m_Window;
	LayerStack m_LayerStack;
	MeasureLayer& m_MeasureLayer;
	WalkLayer& m_WalkLayer;
	AppState m_State;
};
