#pragma once

#include <glm/gtc/type_ptr.hpp>

class Controller
{
public:
    Controller();
    ~Controller();

    glm::vec3 getVelocity();
    bool isKeyPressed(int) const;
};