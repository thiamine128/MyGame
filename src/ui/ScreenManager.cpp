#include "ScreenManager.h"

#include "GameScreen.h"
#include "FailedScreen.h"
#include "Game.h"

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
