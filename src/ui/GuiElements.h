#pragma once

#include "rendering/GuiRenderer.h"
#include <glm/gtc/type_ptr.hpp>

#include <functional>

class Rect
{
public:
    glm::ivec2 lb, rt;

    Rect(glm::ivec2 const&, glm::ivec2 const&);
    bool inside(glm::ivec2 const&) const;
};

class GuiElement
{
public:
    GuiElement();

    Rect const& getRect() const;
    virtual void onClick(int, int);
    virtual void render(GuiRenderer*);
    virtual void onScroll(double);
    void resize(Rect const&);

    void focus();
    void unfocus();
protected:
    Rect rect;
    bool focused;
};

class Button : public GuiElement
{
public:
    Button(std::string const&, float, std::function<void()>);

    virtual void onClick(int, int);
    virtual void render(GuiRenderer*);
    virtual void onScroll(double);
protected:
    std::string text;
    float textSize;
    std::function<void()> func;
};