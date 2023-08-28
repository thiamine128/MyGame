#pragma once

#include "Screen.h"

class FailedScreen : public Screen
{
public:
    FailedScreen(GuiRenderer*);

    virtual void render() const;
    virtual void handleKeyPress(int);
};