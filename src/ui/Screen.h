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
    virtual void handleMouseMove(double, double);
    virtual void handleResize(int, int);
    bool isEscapable() const;
    bool shouldRenderPrev() const;
    int getType() const;
protected:
    GuiRenderer* guiRenderer;
    std::vector<GuiElement*> guiElements;
    bool escapable;
    int screenType;
    bool renderPrev;
};