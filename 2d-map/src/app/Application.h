#pragma once

#include "states/AppState.h"
#include "layers/MeasureLayer.h"
#include "layers/WalkLayer.h"
#include "layers/ModeLayer.h"

#include "../core/Camera.h"
#include "../core/Window.h"
#include "../core/LayerStack.h"

class Application : public IEventListener {
public:
	Application();
	~Application();

	void Run(float targetFps);
	void Update(float deltaTime);
	void Render();
	void OnKey(int key, int action) override;
	void OnMouseMove(double x, double y) override;
	void OnMouseButton(int button, int action) override;

	inline const Window& GetWindow() const { return m_Window; }
	inline Window& GetWindow() { return m_Window; }

	template<typename T, typename... Args>
	T& AddLayer(Args&&... args);
private:
	void InitRenderer();
	void SyncLayersWithState();
	template<typename Event>
	void DispatchToLayers(Event&& eventCallback);
private:
	Input m_Input;
	Window m_Window;
	LayerStack m_LayerStack;
	
	Camera m_Camera;

	ModeLayer& m_ModeLayer;
	WalkLayer& m_WalkLayer;
	MeasureLayer& m_MeasureLayer;

	AppState m_State;

	std::unique_ptr<Renderer2D> m_Renderer;
	std::shared_ptr<Shader> m_QuadShader;

	std::unique_ptr<Texture> m_BackgroundTexture;
};
