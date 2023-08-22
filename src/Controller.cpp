#include "Controller.h"

#include "Window.h"
#include "Game.h"
#include "rendering/GameRenderer.h"
#include "world/item/Item.h"
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
    if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
    {
        Game::getInstance()->getWorld()->getPlayer()->selectItem(key - GLFW_KEY_1);
    }
}

void Controller::processInput()
{
    glfwGetCursorPos(Window::getInstance()->getWindow(), &(this->mouseX), &(this->mouseY));
    if (Window::getInstance()->getKey(GLFW_KEY_SPACE) == GLFW_PRESS)
        Window::getInstance()->close();
    
}

void Controller::onMouseButtonPress(int button, double x, double y) const
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        glm::vec3 pos = Game::getInstance()->getGameRenderer()->getWorldPos(glm::vec2(x, y));
        pos.x = floor(pos.x);
        pos.z = floor(pos.z);
        Player* player = Game::getInstance()->getWorld()->getPlayer();
        Item* item = player->getSelectedItem().item;
        if (item != nullptr)
            item->use(player, glm::ivec2(pos.x, pos.z));
    }
}

double Controller::getMouseX() const
{
    return this->mouseX;
}

double Controller::getMouseY() const
{
    return this->mouseY;
}
