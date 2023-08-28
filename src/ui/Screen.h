#pragma once

#include "rendering/GuiRenderer.h"
#include "GuiElements.h"

class Screen
{
public:
    Screen(GuiRenderer*);
    ~Screen();

    virtual void render() const;
    virtual bool handleClick(int, int) const;
    virtual void handleScroll(int, int, double) const;
    virtual void handleKeyPress(int);
    bool isEscapable() const;
    bool shouldRenderPrev() const;
protected:
    GuiRenderer* guiRenderer;
    std::vector<GuiElement*> guiElements;
    bool escapable;
    bool renderPrev;
};