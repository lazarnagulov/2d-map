#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/VertexArray.h"
#include "core/VertexBuffer.h"
#include "core/Shader.h"
#include "core/Texture.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    float verticesRect[] = {
        -0.2f,  0.2f,    1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.2f, -0.2f,    0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
         0.2f, -0.2f,    0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
         0.2f,  0.2f,    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    };

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
        return -1;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    VertexArray va;
    VertexBuffer vb(verticesRect, 7 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.PushFloat(2);
    layout.PushFloat(3);
    layout.PushFloat(2);
    va.AddBuffer(vb, layout);

    Shader shader("./src/assets/shaders/rect.vert", "./src/assets/shaders/rect.frag");
    shader.Bind();

    Texture texture("./src/assets/textures/twolegs.png");
    texture.Bind();

    shader.SetUniform1i("uTex", 0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}