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
    this->guiRenderer->renderTextCentered(w / 2, h / 2, 2.0, "You Win! Score:" + std::to_string(Game::getInstance()->getWorld()->getScore()));
    this->guiRenderer->renderTextCentered(w / 2, h / 4, 1.0, "Press Space to Conrinue");
    glEnable(GL_DEPTH_TEST);
}

void WinScreen::handleKeyPress(int key)
{
    if (key == GLFW_KEY_SPACE)
    {
        Game* game = Game::getInstance();
        game->getInstance()->quitGame();
        Game::getInstance()->getScreenManager()->popScreen();
        Game::getInstance()->getScreenManager()->popScreen();
    }
}
