#include "Renderer2D.h"
#include <GL/glew.h>

Renderer2D::Renderer2D(const std::shared_ptr<Shader>& shader)
    : m_QuadShader(shader) {
}

void Renderer2D::BeginScene(const glm::mat4& viewProjection)
{
    m_ViewProjection = viewProjection;

    m_QuadShader->Bind();
    m_QuadShader->SetUniformMat4("u_ViewProjection", m_ViewProjection);
}

void Renderer2D::EndScene() { }

void Renderer2D::InitQuad() {
    float vertices[] = {
        -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = { 0,1,2, 2,3,0 };

    m_QuadVA = std::make_unique<VertexArray>();
    m_QuadVB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    m_QuadIB = std::make_unique<IndexBuffer>(indices, 6);

    VertexBufferLayout layout;
    layout.PushFloat(2); 
    layout.PushFloat(2);

    m_QuadVA->AddBuffer(*m_QuadVB, layout);

    m_QuadInitialized = true;
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    if (!m_QuadInitialized)
        InitQuad();

    m_QuadShader->Bind();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

    m_QuadShader->SetUniformMat4("uModel", model);
    m_QuadShader->SetUniform4f("uColor", color);
    m_QuadShader->SetUniform1i("uTex", 0);

    m_QuadVA->Bind();

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, unsigned int textureId)
{
    if (!m_QuadInitialized)
        InitQuad();

    m_QuadShader->Bind();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

    m_QuadShader->SetUniformMat4("uModel", model);
    m_QuadShader->SetUniform1i("uTex", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    m_QuadVA->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}


void Renderer2D::DrawLine(const glm::vec2& p0, const glm::vec2& p1, float thickness, const glm::vec4& color) {
    glm::vec2 direction = p1 - p0;
    float lenght = glm::length(direction);
    
    if (lenght <= 0.0001f) 
        return;
    
    glm::vec2 mid = p1 + direction * 0.5f;
    float angle = std::atan2(direction.y, direction.x);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(mid, 0.0f));
    model = glm::rotate(model, angle, glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(lenght, thickness, 1.0f)); 

    m_ColorShader->Bind();
    m_ColorShader->SetUniformMat4("uModel", model);
    m_ColorShader->SetUniform4f("uColor", color);

    if (!m_QuadInitialized)
        InitQuad();
    
    m_QuadVA->Bind();
    m_QuadIB->Bind();
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer2D::DrawCircle(const glm::vec2& center, float radius, const glm::vec4& color) {

}

void Renderer2D::DrawText(const std::string& txt, glm::vec2 pos, float scale = 1.0f) {

}

void Renderer2D::DrawOverlay(const Texture& tex, glm::vec2 pos, glm::vec2 size, float alpha) {

}
