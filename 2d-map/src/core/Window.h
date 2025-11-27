#pragma once

#include <GLFW/glfw3.h>
#include "Input.h"

class Window {
public:
	Window(Input& input);
	~Window();

	inline bool ShouldClose() const { return glfwWindowShouldClose(m_Window); };
	void ApplyLetterbox(float targetAspectRatio = 1.0f);
	void Update();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline GLFWwindow* GetWindow() const { return m_Window;  }
private:
	void InitGLFW();
	void CreateFullscreenWindow();
	void InitGLEW();
	void SetupCallbacks();
private:
	int m_Width;
	int m_Height;
	GLFWwindow* m_Window;
	Input& m_Input;
};
