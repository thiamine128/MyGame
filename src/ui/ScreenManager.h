#pragma once

#include "Screen.h"
#include "rendering/GuiRenderer.h"

class ScreenManager
{
public:
    ScreenManager(GuiRenderer*);

    Screen* getTopScreen() const;
    void render() const;
    void popScreen();
    void pushGameScreen();
protected:
    GuiRenderer* guiRenderer;
    Screen* screens[16];
    int stackTop;
};