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

	inline GLFWwindow* GetWindow() const { return m_Window;  }
private:
	void InitGLFW();
	void CreateFullscreenWindow();
	void InitGLEW();
	void SetupCallbacks();
private:
	GLFWwindow* m_Window;
	Input& m_Input;
};
