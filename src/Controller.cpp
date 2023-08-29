#include "Controller.h"

#include "Window.h"
#include "Game.h"
#include "rendering/WorldRenderer.h"
#include "SoundManager.h"
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
    const float speed = 1.0;
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
    if (key == GLFW_KEY_ESCAPE)
    {
        Game::getInstance()->getScreenManager()->escape();
    }
    Game::getInstance()->getScreenManager()->handleKeyPress(key);
    SoundManager::play("assets/sounds/splat.mp3");
}

void Controller::processInput()
{

}

void Controller::onMouseButtonPress(int button, double x, double y) const
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        Game::getInstance()->getScreenManager()->handleClick(x, Window::getInstance()->getHeight() - y);
    }
}

void Controller::onScroll(double xOff, double yOff) const
{
    Game::getInstance()->getScreenManager()->handleScroll(this->mouseX, Window::getInstance()->getHeight() - this->mouseY, yOff);
}

void Controller::onCursorMove(double x, double y)
{
    this->mouseX = x;
    this->mouseY = y;
    Game::getInstance()->getScreenManager()->onCursorMove(mouseX, Window::getInstance()->getHeight() - mouseY);
}

double Controller::getMouseX() const
{
    return this->mouseX;
}

double Controller::getMouseY() const
{
    return this->mouseY;
}
