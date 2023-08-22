#include "ScreenManager.h"

#include "GameScreen.h"
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

void ScreenManager::render() const
{
    if (this->getTopScreen() != nullptr)
    {
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