#include "MenuScreen.h"

#include "Game.h"
#include "Window.h"

MenuScreen::MenuScreen(GuiRenderer* guiRenderer) : Screen(guiRenderer)
{
    this->screenType = 3;

    int w = Window::getInstance()->getWidth(), h = Window::getInstance()->getHeight();
    this->guiElements.push_back(new Button("New Game", 1.0f, [](void){Game::getInstance()->startNewGame();}));
    this->guiElements.push_back(new Button("Quit", 1.0f, [](void){Window::getInstance()->close();}));
    this->handleResize(w, h);
}

void MenuScreen::render() const
{
    glDisable(GL_DEPTH_TEST);
    int w = Window::getInstance()->getWidth(), h = Window::getInstance()->getHeight();
    guiRenderer->renderRect(0, 0, w, h, glm::vec4(0.4, 0.8, 0.0, 1.0));
    this->guiRenderer->renderTextCentered(w / 2, h / 4 * 3, 2.0f, "The Binding of Peashooter");
    Screen::render();
    glEnable(GL_DEPTH_TEST);
}

void MenuScreen::handleKeyPress(int)
{
}

void MenuScreen::handleResize(int w, int h)
{
    this->guiElements[0]->resize({{w / 2 - 100, h / 2 - 50}, {w / 2 + 100, h / 2 + 50}});
    this->guiElements[1]->resize({{w / 2 - 100, h / 2 - 180}, {w / 2 + 100, h / 2 - 80}});
}
