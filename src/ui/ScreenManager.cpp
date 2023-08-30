#include "ScreenManager.h"

#include "GameScreen.h"
#include "FailedScreen.h"
#include "MenuScreen.h"
#include "PauseScreen.h"
#include "WinScreen.h"
#include "HelpScreen.h"
#include "Game.h"
#include "Window.h"

ScreenManager::ScreenManager(GuiRenderer* guiRenderer) : guiRenderer(guiRenderer)
{
    this->stackTop = -1;
}

Screen *ScreenManager::getTopScreen() const
{
    if (this->stackTop < 0)
        return nullptr;
    else
        return this->screens[this->stackTop];
}

Screen *ScreenManager::getPrevScreen() const
{
    if (this->stackTop < 1)
        return nullptr;
    else
        return this->screens[this->stackTop - 1];
}

void ScreenManager::render() const
{
    if (this->getTopScreen() != nullptr)
    {
        if (this->getTopScreen()->shouldRenderPrev() && this->getPrevScreen() != nullptr)
        {
            this->getPrevScreen()->render();
        }
        this->getTopScreen()->render();
    }
}

void ScreenManager::popScreen()
{
    if (this->stackTop >= 0)
    {
        delete this->screens[this->stackTop];
        --(this->stackTop);
    }
}

void ScreenManager::pushGameScreen()
{
    this->screens[++(this->stackTop)] = new GameScreen(this->guiRenderer, Game::getInstance()->getWorldRenderer());
}

void ScreenManager::pushFailedScreen()
{
    this->screens[++(this->stackTop)] = new FailedScreen(this->guiRenderer);
}

void ScreenManager::pushMenuScreen()
{
    this->screens[++(this->stackTop)] = new MenuScreen(this->guiRenderer);
}

void ScreenManager::pushPauseScreen()
{
    this->screens[++(this->stackTop)] = new PauseScreen(this->guiRenderer);
}

void ScreenManager::pushWinScreen()
{
    this->screens[++(this->stackTop)] = new WinScreen(this->guiRenderer);
}

void ScreenManager::pushHelpScreen()
{
    this->screens[++(this->stackTop)] = new HelpScreen(this->guiRenderer);
}

void ScreenManager::escape()
{
    if (this->getTopScreen() != nullptr)
    {
        if (this->getTopScreen()->isEscapable())
        {
            this->popScreen();
        }
    }
}

void ScreenManager::onCursorMove(double x, double y)
{
    this->getTopScreen()->handleMouseMove(x, y);
}

bool ScreenManager::inGameScreen() const
{
    return this->getTopScreen()->getType() == 1;
}

void ScreenManager::handleClick(int x, int y) const
{
    if (this->getTopScreen() != nullptr)
    {
        this->getTopScreen()->handleClick(x, y);
    }
}

void ScreenManager::handleScroll(int x, int y, double yOff) const
{
    if (this->getTopScreen() != nullptr)
    {
        this->getTopScreen()->handleScroll(x, y, yOff);
    }
}

void ScreenManager::handleKeyPress(int key) const
{
    if (this->getTopScreen() != nullptr)
    {
        this->getTopScreen()->handleKeyPress(key);
    }
}

void ScreenManager::handleResize(int w, int h)
{
    for (int i = 0; i <= stackTop; ++i)
        screens[i]->handleResize(w, h);
}
