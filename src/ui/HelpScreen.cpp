#include "HelpScreen.h"

#include "Window.h"
#include "Game.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

HelpScreen::HelpScreen(GuiRenderer* guiRenderer) : Screen(guiRenderer)
{
    this->renderPrev = true;
    this->screenType = 2;
    this->escapable = true;
}

void HelpScreen::render() const
{
    glDisable(GL_DEPTH_TEST);
    int w = Window::getInstance()->getWidth(), h = Window::getInstance()->getHeight();
    guiRenderer->renderRect(0, 0, w, h, glm::vec4(0.2, 0.2, 0.2, 0.8));
    this->guiRenderer->renderTextCentered(w / 2, h / 6 * 5, 1.5, "Move: WASD");
    this->guiRenderer->renderTextCentered(w / 2, h / 6 * 4, 1.5, "Shoot: Arrows");
    this->guiRenderer->renderTextCentered(w / 2, h / 6 * 3, 1.5, "Pause: Esc");
    this->guiRenderer->renderTextCentered(w / 2, h / 6 * 2, 1.5, "Map: M");
    glEnable(GL_DEPTH_TEST);
}

void HelpScreen::handleKeyPress(int key)
{
    
}
