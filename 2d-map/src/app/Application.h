#pragma once

#include "AppState.h"
#include "layers/MeasureLayer.h"
#include "layers/WalkLayer.h"
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
	void UpdateProjection();

	template<typename Event>
	void DispatchToLayers(Event&& eventCallback);

private:
	Input m_Input;
	Window m_Window;
	LayerStack m_LayerStack;
	MeasureLayer& m_MeasureLayer;
	WalkLayer& m_WalkLayer;
	AppState m_State;

	std::unique_ptr<Renderer2D> m_Renderer;
	std::shared_ptr<Shader> m_QuadShader;
	glm::mat4 m_Projection;
	

	std::unique_ptr<Texture> m_BackgroundTexture;
};
