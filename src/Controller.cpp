#include "Controller.h"

#include "Window.h"
#include "Game.h"
#include <GLFW/glfw3.h>

#include <iostream>

Controller::Controller()
{
}

Controller::~Controller()
{
}

glm::vec3 Controller::getVelocity()
{
    const float speed = 2.0;
    glm::vec3 ret = glm::vec3(0.0);
    if (this->isKeyPressed(GLFW_KEY_W))
        ret.z += speed;
    if (this->isKeyPressed(GLFW_KEY_A))
        ret.x += speed;
    if (this->isKeyPressed(GLFW_KEY_S))
        ret.z -= speed;
    if (this->isKeyPressed(GLFW_KEY_D))
        ret.x -= speed;
    return ret;
}

bool Controller::isKeyPressed(int key) const
{
    return Window::getInstance()->getKey(key) == GLFW_PRESS;
}

void Controller::onPress(int key) const
{
    if (key == GLFW_KEY_E) {
        Game::getInstance()->getWorld()->getPlayer()->plow();
    }
}
