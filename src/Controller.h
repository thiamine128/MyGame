#pragma once

#include <glm/gtc/type_ptr.hpp>

class Controller
{
public:
    Controller();
    ~Controller();

    glm::vec3 getVelocity();
    bool isKeyPressed(int) const;
    void onPress(int) const;
    void processInput();
    void onMouseButtonPress(int, double, double) const;
    void onScroll(double, double) const;
    double getMouseX() const;
    double getMouseY() const;
protected:
    double mouseX, mouseY;
};