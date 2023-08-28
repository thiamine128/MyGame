#include "PauseScreen.h"

#include "Window.h"
#include "Game.h"

#include <GLFW/glfw3.h>

PauseScreen::PauseScreen(GuiRenderer* guiRenderer) : Screen(guiRenderer)
{
    this->screenType = 4;
    this->renderPrev = true;
}

void PauseScreen::render() const
{
    glDisable(GL_DEPTH_TEST);
    int w = Window::getInstance()->getWidth(), h = Window::getInstance()->getHeight();
    guiRenderer->renderRect(0, 0, w, h, glm::vec4(0.2));
    guiRenderer->renderTextCentered(w / 2, h / 2, 1.5f, "Game Paused");
    guiRenderer->renderTextCentered(w / 2, h / 4, 1.5f, "Press Space to Continue");
    Screen::render();
    glEnable(GL_DEPTH_TEST);
}

void PauseScreen::handleKeyPress(int key)
{
    if (key == GLFW_KEY_SPACE)
    {
        Game::getInstance()->continueGame();
    }
}
