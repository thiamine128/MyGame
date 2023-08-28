#include "FailedScreen.h"

#include "Window.h"
#include "Game.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

FailedScreen::FailedScreen(GuiRenderer* guiRenderer) : Screen(guiRenderer)
{
    this->renderPrev = true;
    this->screenType = 2;
}

void FailedScreen::render() const
{
    glDisable(GL_DEPTH_TEST);
    int w = Window::getInstance()->getWidth(), h = Window::getInstance()->getHeight();
    guiRenderer->renderRect(0, 0, w, h, glm::vec4(0.2));
    this->guiRenderer->renderTextCentered(w / 2, h / 2, 2.0, "You Failed");
    this->guiRenderer->renderTextCentered(w / 2, h / 4, 1.0, "Press Space to Restart");
    glEnable(GL_DEPTH_TEST);
}

void FailedScreen::handleKeyPress(int key)
{
    if (key == GLFW_KEY_SPACE)
    {
        Game* game = Game::getInstance();
        game->getInstance()->getScreenManager()->popScreen();
        game->newGame();
    }
}
