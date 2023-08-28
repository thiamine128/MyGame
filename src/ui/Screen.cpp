#include "Screen.h"

#include <iostream>

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

void Screen::handleMouseMove(double x, double y)
{
    for (auto g : guiElements)
    {
        if (g->getRect().inside(glm::ivec2(x, y)))
        {
            g->focus();
        } else
        {
            g->unfocus();
        }
    }
}

void Screen::handleResize(int w, int h)
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

int Screen::getType() const
{
    return this->screenType;
}
