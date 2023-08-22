#pragma once

#include "rendering/GuiRenderer.h"

class Screen
{
public:
    Screen(GuiRenderer*);

    virtual void render() const;
protected:
    GuiRenderer* guiRenderer;
};