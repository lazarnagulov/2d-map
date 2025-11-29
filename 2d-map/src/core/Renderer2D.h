#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Renderer2D
{
public:
    Renderer2D(const std::shared_ptr<Shader>& shader);


    void BeginScene(const glm::mat4& viewProjection);
    void EndScene();

    void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);

    void DrawLine(const glm::vec2& p0, const glm::vec2& p1, float thickness, const glm::vec4& color);

    void DrawCircle(const glm::vec2& center, float radius, const glm::vec4& color, bool filled = true);
    void DrawCircleOutline(const glm::vec2& center, float radius, float thickness, const glm::vec4& color);


private:
    void InitQuad();
    void InitLine();
    void InitCircle();

private:
    std::shared_ptr<Shader> m_QuadShader;
    std::shared_ptr<Shader> m_ColorShader;
    std::shared_ptr<Shader> m_CircleShader;
    std::shared_ptr<Shader> m_TextShader;

    std::unique_ptr<VertexArray> m_QuadVA;
    std::unique_ptr<VertexBuffer> m_QuadVB;
    std::unique_ptr<IndexBuffer> m_QuadIB;
    bool m_QuadInitialized = false;

    std::unique_ptr<VertexArray> m_LineVA;
    std::unique_ptr<VertexBuffer> m_LineVB;
    std::unique_ptr<IndexBuffer> m_LineIB;
    bool m_LineInitialized = false;

    std::unique_ptr<VertexArray> m_CircleVA;
    std::unique_ptr<VertexBuffer> m_CircleVB;
    std::unique_ptr<IndexBuffer> m_CircleIB;
    bool m_CircleInitialized = false;
    unsigned int m_CircleSegments = 64;
    
    glm::mat4 m_ViewProjection = glm::mat4(1.0f);
};