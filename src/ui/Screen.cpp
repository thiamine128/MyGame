#include "Screen.h"

Screen::Screen(GuiRenderer* guiRenderer) : guiRenderer(guiRenderer)
{
    this->escapable = false;
    this->renderPrev = false;
}

Screen::~Screen()
{
    glDisable(GL_DEPTH_TEST);
    for (auto guiElement : guiElements)
    {
        delete guiElement;
    }
}

void Screen::render() const
{
    for (auto guiElement : guiElements)
    {
        guiElement->render(this->guiRenderer);
    }
}

bool Screen::handleClick(int x, int y) const
{
    for (auto guiElement : guiElements)
    {
        if (guiElement->getRect().inside({x, y}))
        {
            guiElement->onClick(x, y);
            return true;
        }
    }
    return false;
}

void Screen::handleScroll(int x, int y, double yOff) const
{
    for (auto guiElement : guiElements)
    {
        if (guiElement->getRect().inside({x, y}))
        {
            guiElement->onScroll(yOff);
        }
    }
}

void Screen::handleKeyPress(int)
{
}

bool Screen::isEscapable() const
{
    return this->escapable;
}

bool Screen::shouldRenderPrev() const
{
    return this->renderPrev;
}
