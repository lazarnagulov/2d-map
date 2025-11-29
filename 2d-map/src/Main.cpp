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
#include "app/Application.h"
#include "core/Renderer2D.h"

int main(void) {
    Application app;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int screenWidth = app.GetWindow().GetWidth();
    int screenHeight = app.GetWindow().GetHeight();

    auto quadShader = std::make_shared<Shader>("./src/assets/shaders/quad.vert", "./src/assets/shaders/quad.frag");
    Renderer2D renderer(quadShader);
    Texture texture("./src/assets/textures/map.jpg");
    texture.Bind();

    glm::mat4 projection = glm::ortho(
        0.0f, static_cast<float>(screenWidth),    
        0.0f, static_cast<float>(screenHeight),
        -1.0f, 1.0f         
    );


    int mapHeight = texture.GetHeight();
    int mapWidth = texture.GetWidth();

    FrameLimiter frameLimiter(75);

    while (!app.GetWindow().ShouldClose())
    {
        if (frameLimiter.ShouldRender())
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glViewport(0, 0, screenWidth, screenHeight);

            renderer.BeginScene(projection);

            renderer.DrawQuad(
                glm::vec2(screenWidth / 2, screenHeight / 2),
                glm::vec2(mapWidth, mapHeight),
                texture
            );

            renderer.EndScene();
            app.Update(frameLimiter.GetDeltaTime());
        }

    }

    glfwTerminate();
    return 0;
}