#include "WinScreen.h"

#include "Window.h"
#include "Game.h"

#include <GLFW/glfw3.h>

WinScreen::WinScreen(GuiRenderer* guiRenderer) : Screen(guiRenderer)
{
    this->renderPrev = true;
    this->screenType = 2;
}

void WinScreen::render() const
{
    glDisable(GL_DEPTH_TEST);
    int w = Window::getInstance()->getWidth(), h = Window::getInstance()->getHeight();
    guiRenderer->renderRect(0, 0, w, h, glm::vec4(0.2));
    std::string rec = ((Game::getInstance()->getWorld()->newRec) ? "(Record)" : "");
    this->guiRenderer->renderTextCentered(w / 2, h / 2, 2.0, "You Win!");
    this->guiRenderer->renderTextCentered(w / 2, h / 3, 1.0, "Score" + rec +  ":" + std::to_string(Game::getInstance()->getWorld()->getScore()));
    this->guiRenderer->renderTextCentered(w / 2, h / 4, 1.0, "Press Space to Conrinue");
    glEnable(GL_DEPTH_TEST);
}

void WinScreen::handleKeyPress(int key)
{
    if (key == GLFW_KEY_SPACE)
    {
        Game* game = Game::getInstance();
        Game::getInstance()->getScreenManager()->popScreen();
        Game::getInstance()->getScreenManager()->popScreen();
    }
}
