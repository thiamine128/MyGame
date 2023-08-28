#pragma once

#include "Screen.h"

class PauseScreen : public Screen
{
public:
    PauseScreen(GuiRenderer*);

    virtual void render() const;
    virtual void handleKeyPress(int);
};