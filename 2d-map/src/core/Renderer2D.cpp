#include "Renderer2D.h"
#include <GL/glew.h>

Renderer2D::Renderer2D(const std::shared_ptr<Shader>& shader)
    : m_QuadShader(shader) { }

void Renderer2D::BeginScene(const glm::mat4& viewProjection) {
    m_ViewProjection = viewProjection;

    if (m_QuadShader) {
        m_QuadShader->Bind();
        m_QuadShader->SetUniformMat4("uViewProjection", m_ViewProjection);
    }
}

void Renderer2D::EndScene() { }

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
    if (!m_QuadInitialized)
        InitQuad();

    m_QuadShader->Bind();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));

    if (rotation != 0.0f)
        model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    m_QuadShader->SetUniformMat4("uModel", model);
    m_QuadShader->SetUniform4f("uColor", color);
    m_QuadShader->SetUniform1i("uTex", 0);

    m_QuadVA->Bind();
    m_QuadIB->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    DrawQuad(position, size, 0.0f, color);
}

void Renderer2D::DrawLine(const glm::vec2& p0, const glm::vec2& p1, float thickness, const glm::vec4& color) {
    if (!m_LineInitialized)
        InitLine();

    glm::vec2 direction = p1 - p0;
    float length = glm::length(direction);

    if (length < 0.0001f)
        return;

    glm::vec2 mid = p0 + direction * 0.5f;
    float angle = std::atan2(direction.y, direction.x);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(mid, 0.0f));
    model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(length, thickness, 1.0f));

    m_QuadShader->Bind();
    m_QuadShader->SetUniformMat4("uModel", model);
    m_QuadShader->SetUniform4f("uColor", color);
    m_QuadShader->SetUniform1i("uTex", 0);

    m_LineVA->Bind();
    m_LineIB->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer2D::DrawCircle(const glm::vec2& center, float radius, const glm::vec4& color, bool filled) {
    if (filled) {
        if (!m_CircleInitialized)
            InitCircle();

        m_QuadShader->Bind();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(center, 0.0f))
            * glm::scale(glm::mat4(1.0f), glm::vec3(radius * 2.0f, radius * 2.0f, 1.0f));

        m_QuadShader->SetUniformMat4("uModel", model);
        m_QuadShader->SetUniform4f("uColor", color);
        m_QuadShader->SetUniform1i("uTex", 0);

        m_CircleVA->Bind();
        m_CircleIB->Bind();

        glDrawElements(GL_TRIANGLES, m_CircleSegments * 3, GL_UNSIGNED_INT, nullptr);
    }
    else {
        DrawCircleOutline(center, radius, 2.0f, color);
    }
}

void Renderer2D::DrawCircleOutline(const glm::vec2& center, float radius, float thickness, const glm::vec4& color) {
    const int segments = 64;

    for (int i = 0; i < segments; ++i) {
        float angle1 = (float)i / (float)segments * 2.0f * 3.14159265359f;
        float angle2 = (float)(i + 1) / (float)segments * 2.0f * 3.14159265359f;

        glm::vec2 p1 = center + glm::vec2(std::cos(angle1), std::sin(angle1)) * radius;
        glm::vec2 p2 = center + glm::vec2(std::cos(angle2), std::sin(angle2)) * radius;

        DrawLine(p1, p2, thickness, color);
    }
}

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


void Renderer2D::InitLine() {
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = { 0,1,2, 2,3,0 };

    m_LineVA = std::make_unique<VertexArray>();
    m_LineVB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    m_LineIB = std::make_unique<IndexBuffer>(indices, 6);

    VertexBufferLayout layout;
    layout.PushFloat(2); 
    m_LineVA->AddBuffer(*m_LineVB, layout);

    m_LineInitialized = true;
}

void Renderer2D::InitCircle() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    vertices.push_back(0.0f);
    vertices.push_back(0.0f);

    for (unsigned int i = 0; i <= m_CircleSegments; ++i) {
        float angle = (float)i / (float)m_CircleSegments * 2.0f * 3.14159265359f;
        float x = std::cos(angle) * 0.5f;
        float y = std::sin(angle) * 0.5f;
        vertices.push_back(x);
        vertices.push_back(y);
    }

    for (unsigned int i = 1; i <= m_CircleSegments; ++i) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    m_CircleVA = std::make_unique<VertexArray>();
    m_CircleVB = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float));
    m_CircleIB = std::make_unique<IndexBuffer>(indices.data(), indices.size());

    VertexBufferLayout layout;
    layout.PushFloat(2);
    m_CircleVA->AddBuffer(*m_CircleVB, layout);

    m_CircleInitialized = true;
}