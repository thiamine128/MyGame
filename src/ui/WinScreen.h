#pragma once

#include "Screen.h"

class WinScreen : public Screen
{
public:
    WinScreen(GuiRenderer*);

    virtual void render() const;
    virtual void handleKeyPress(int);
};