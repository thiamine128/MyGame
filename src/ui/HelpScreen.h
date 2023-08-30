#pragma once

#include "Screen.h"

class HelpScreen : public Screen
{
public:
    HelpScreen(GuiRenderer*);

    virtual void render() const;
    virtual void handleKeyPress(int);
};