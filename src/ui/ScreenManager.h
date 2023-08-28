#pragma once

#include "Screen.h"
#include "rendering/GuiRenderer.h"

class ScreenManager
{
public:
    ScreenManager(GuiRenderer*);

    Screen* getTopScreen() const;
    Screen* getPrevScreen() const;
    void render() const;
    void popScreen();
    void pushGameScreen();
    void pushFailedScreen();
    void escape();
    void handleInput();
    void handleClick(int, int) const;
    void handleScroll(int, int, double) const;
    void handleKeyPress(int) const;
protected:
    GuiRenderer* guiRenderer;
    Screen* screens[16];
    int stackTop;
};