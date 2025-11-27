#pragma once

#include <list>

#include "glm/glm.hpp"

struct AppState {
    enum Mode { WALK, MEASURE } currentMode;
    
    glm::vec2 cameraPos;
    float walkedDistance;

    std::list<glm::vec2> points;
    float measuredDistance;
};