#pragma once

#include "Screen.h"

class MenuScreen : public Screen
{
public:
    MenuScreen(GuiRenderer*);
    
    virtual void render() const;
    virtual void handleKeyPress(int);
    virtual void handleResize(int, int);

protected:
    const Texture* bg;
};