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
    void pushMenuScreen();
    void pushPauseScreen();
    void pushWinScreen();
    void escape();
    void onCursorMove(double, double);
    bool inGameScreen() const;
    void handleClick(int, int) const;
    void handleScroll(int, int, double) const;
    void handleKeyPress(int) const;
    void handleResize(int, int);
protected:
    GuiRenderer* guiRenderer;
    Screen* screens[16];
    int stackTop;
};