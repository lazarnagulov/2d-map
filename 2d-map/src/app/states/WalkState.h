#pragma once
#include <glm/glm.hpp>

class WalkState {
public:
    enum MoveDirection : uint8_t {
        NONE = 0,
        UP = 1 << 0, 
        DOWN = 1 << 1,
        LEFT = 1 << 2, 
        RIGHT = 1 << 3 
    };

    WalkState(const glm::vec2& startPosition = { 0.0f, 0.0f });

    void Update(float deltaTime, uint8_t directions);
    void Reset();

    inline glm::vec2 GetPosition() const { return m_Position; }
    inline float GetWalkedDistance() const { return m_WalkedDistance; }
private:
    glm::vec2 m_Position;
    float m_WalkedDistance;
    float m_MoveSpeed;
};