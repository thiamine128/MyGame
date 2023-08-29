#include "MenuScreen.h"

#include "Game.h"
#include "Window.h"
#include "TextureManager.h"

MenuScreen::MenuScreen(GuiRenderer* guiRenderer) : Screen(guiRenderer)
{
    this->screenType = 3;

    int w = Window::getInstance()->getWidth(), h = Window::getInstance()->getHeight();
    this->guiElements.push_back(new Button("New Game", 1.0f, [](void){Game::getInstance()->startNewGame();}));
    this->guiElements.push_back(new Button("Quit", 1.0f, [](void){Window::getInstance()->close();}));
    this->handleResize(w, h);

    this->bg = TextureManager::getTexture("assets/textures/background.png");
}

void MenuScreen::render() const
{
    glDisable(GL_DEPTH_TEST);
    int w = Window::getInstance()->getWidth(), h = Window::getInstance()->getHeight();
    guiRenderer->renderImage(0, 0, w, h, bg);
    this->guiRenderer->renderTextCentered(w / 2, h / 4 * 3, 2.0f, "The Binding of Peas");
    Screen::render();
    glEnable(GL_DEPTH_TEST);
}

void MenuScreen::handleKeyPress(int)
{
}

void MenuScreen::handleResize(int w, int h)
{
    this->guiElements[0]->resize({{w / 2 - 100, h / 2 - 50}, {w / 2 + 100, h / 2 + 50}});
    this->guiElements[1]->resize({{w / 2 - 100, h / 2 - 150}, {w / 2 + 100, h / 2 - 50}});
}