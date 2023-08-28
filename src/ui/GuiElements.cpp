#include "GuiElements.h"

#include <iostream>

Rect::Rect(glm::ivec2 const& lb, glm::ivec2 const& rt) : lb(lb), rt(rt)
{
}

bool Rect::inside(glm::ivec2 const& pos) const
{
    return pos.x >= lb.x && pos.x <= rt.x
        && pos.y >= lb.y && pos.y <= rt.y;
}

GuiElement::GuiElement() : rect({0, 0}, {0, 0})
{

}

void GuiElement::focus()
{
    this->focused = true;
}

void GuiElement::unfocus()
{
    this->focused = false;
}

Rect const &GuiElement::getRect() const
{
    return this->rect;
}

void GuiElement::onClick(int x, int y)
{
}

void GuiElement::render(GuiRenderer *)
{
}

void GuiElement::onScroll(double)
{
}

void GuiElement::resize(Rect const& rect)
{
    this->rect = rect;
}

Button::Button(std::string const& text, float textSize, std::function<void()> func) : text(text), func(func), textSize(textSize)
{

}

void Button::onClick(int x, int y)
{
    this->func();
}

void Button::render(GuiRenderer* guiRenderer)
{
    guiRenderer->renderTextCentered((rect.lb.x + rect.rt.x) >> 1, (rect.lb.y + rect.rt.y) >> 1, this->textSize + (focused ? 0.5f : 0.0f), this->text);
}

void Button::onScroll(double yOff)
{
    
}
