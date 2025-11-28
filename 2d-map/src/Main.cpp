#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "core/VertexArray.h"
#include "core/VertexBuffer.h"
#include "core/Shader.h"
#include "core/Texture.h"
#include "core/Input.h"
#include "core/Window.h"
#include "core/Camera.h"
#include "core/FrameLimiter.h"

int main(void)
{
    Input input;
    Window window(input);
    int screenWidth = window.GetWidth();
    int screenHeight = window.GetHeight();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Texture texture("./src/assets/textures/map.jpg");
    texture.Bind();

    int mapHeight = texture.GetHeight();
    int mapWidth = texture.GetWidth();

    float verticesRect[] = {
        0.0f,         0.0f,          0.0f, 1.0f, 
        0.0f,         screenHeight,  0.0f, 0.0f, 
        screenWidth,  screenHeight,  1.0f, 0.0f,
        screenWidth,  0.0f,          1.0f, 1.0f  
    };

    VertexArray va;
    VertexBuffer vb(verticesRect, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.PushFloat(2);
    layout.PushFloat(2); 
    va.AddBuffer(vb, layout);

    float zoom = 1.0f;
    Shader shader("./src/assets/shaders/texture.vert", "./src/assets/shaders/texture.frag");
    shader.Bind();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    float halfW = (float)screenWidth * 0.5f;
    float halfH = (float)screenHeight * 0.5f;

    float left = halfW - halfW * zoom;
    float right = halfW + halfW * zoom;
    float bottom = halfH - halfH * zoom;
    float top = halfH + halfH * zoom;

    glm::mat4 proj = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

    shader.SetUniform1i("uTex", 0);
    shader.SetUniformMat4("uModel", model);
    shader.SetUniformMat4("uView", view);
    shader.SetUniformMat4("uProj", proj);

    FrameLimiter frameLimiter(75);

    while (!window.ShouldClose())
    {
        if (frameLimiter.ShouldRender())
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glViewport(0, 0, screenWidth, screenHeight);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

            window.Update();
        }
    }

    glfwTerminate();
    return 0;
}