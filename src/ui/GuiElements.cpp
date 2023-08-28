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

GuiElement::GuiElement(Rect const& rect) : rect(rect)
{

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

Button::Button(Rect const& rect, std::string const& text, std::function<void()> func) : GuiElement(rect), text(text), func(func)
{

}

void Button::onClick(int x, int y)
{
    this->func();
}

void Button::render(GuiRenderer* guiRenderer)
{
    guiRenderer->renderRect(rect.lb.x, rect.lb.y, rect.rt.x, rect.rt.y, glm::vec4(1.0));
    guiRenderer->renderTextCentered((rect.lb.x + rect.rt.x) >> 1, (rect.lb.y + rect.rt.y) >> 1, 0.5f, this->text);
}

void Button::onScroll(double yOff)
{
    std::cout << "Scroll : " << yOff << std::endl;
}
