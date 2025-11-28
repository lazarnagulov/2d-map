#include <GL/glew.h>
#include <iostream>

#include "Window.h"

Window::Window(Input& input) : m_Input(input), m_Window(nullptr) {
    InitGLFW();
    CreateFullscreenWindow();
    InitGLEW();
    SetupCallbacks();
}

Window::~Window() {
    glfwTerminate();
}

void Window::InitGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        std::exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::CreateFullscreenWindow() {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    m_Width = mode->width;
    m_Height = mode->height;
    m_Window = glfwCreateWindow(m_Width, m_Height, "2D map", monitor, nullptr);

    if (!m_Window) {
        std::cerr << "Window creation failed\n";
        glfwTerminate();
        std::exit(-1);
    }

    glfwMakeContextCurrent(m_Window);
}

void Window::SetupCallbacks() {
    glfwSetWindowUserPointer(m_Window, &m_Input);

    glfwSetKeyCallback(m_Window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
        auto* input = static_cast<Input*>(glfwGetWindowUserPointer(win));
        input->OnKeyEvent(key, action);

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(win, true);
        });
}

void Window::InitGLEW() {
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW init failed\n";
        std::exit(-1);
    }
}

void Window::Update() { 
    glfwSwapBuffers(m_Window); 
    glfwPollEvents(); 
}


void Window::ApplyLetterbox(float targetAspectRatio /* = 1.0f*/) {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(m_Window, &windowWidth, &windowHeight);

    float windowAspect = (float)windowWidth / (float)windowHeight;

    int renderWidth, renderHeight;

    if (windowAspect > targetAspectRatio) {
        renderHeight = windowHeight;
        renderWidth = (int)(windowHeight * targetAspectRatio);
    }
    else {
        renderWidth = windowWidth;
        renderHeight = (int)(windowWidth / targetAspectRatio);
    }

    int offsetX = (windowWidth - renderWidth) / 2;
    int offsetY = (windowHeight - renderHeight) / 2;

    glViewport(offsetX, offsetY, renderWidth, renderHeight);
}