#pragma once

#include <memory>
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
    void DrawQuad(const glm::vec2& position, const glm::vec2& size, unsigned textureID);
    void DrawLine(const glm::vec2& p0, const glm::vec2& p1, float thickness, const glm::vec4& color);
    void DrawCircle(const glm::vec2& center, float radius, const glm::vec4& color);
    void DrawText(const std::string& txt, glm::vec2 pos, float scale = 1.0f);
    void DrawOverlay(const Texture& tex, glm::vec2 pos, glm::vec2 size, float alpha);

private:
    void InitQuad();

private:
    std::shared_ptr<Shader> m_QuadShader;
    std::shared_ptr<Shader> m_ColorShader;

    std::unique_ptr<VertexArray> m_QuadVA;
    std::unique_ptr<VertexBuffer> m_QuadVB;
    std::unique_ptr<IndexBuffer> m_QuadIB;

    bool m_QuadInitialized = false;
    glm::mat4 m_ViewProjection = glm::mat4(1.0f);
};
