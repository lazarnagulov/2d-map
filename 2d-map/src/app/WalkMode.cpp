#include "WalkMode.h"

WalkMode::WalkMode(const glm::vec2& startPosition /*= { 0.0f, 0.0f }*/)
	: m_Position(startPosition), m_WalkedDistance(0), m_MoveSpeed(200.0f)
{}

void WalkMode::Update(float deltaTime, uint8_t directions) {
    glm::vec2 movement(0.0f);

    if (directions & UP)    movement.y += 1.0f;
    if (directions & DOWN)  movement.y -= 1.0f;
    if (directions & LEFT)  movement.x -= 1.0f;
    if (directions & RIGHT) movement.x += 1.0f;


    if (glm::length(movement) > 0.0f) {
        movement = glm::normalize(movement);
        glm::vec2 delta = movement * m_MoveSpeed * deltaTime;
        m_Position += delta;
        m_WalkedDistance += glm::length(delta);
    }
}

void WalkMode::Reset() {
	m_Position = glm::vec2(0.0f);
	m_WalkedDistance = 0.0f;
}
