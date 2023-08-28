#include "GameScreen.h"

#include "Game.h"
#include "Window.h"
#include "TextureManager.h"
#include "ModelManager.h"

#include <GLFW/glfw3.h>
#include <iostream>

GameScreen::GameScreen(GuiRenderer* guiRenderer, WorldRenderer* worldRenderer) : Screen(guiRenderer), worldRenderer(worldRenderer)
{
    this->escapable = false;
}

void GameScreen::render() const
{
    this->worldRenderer->render();

    glDisable(GL_CULL_FACE);

    int height = Window::getInstance()->getHeight();
    int healthSize = height / 20;

    Player* player = Game::getInstance()->getWorld()->getPlayer();
    int hearts = player->getHearts();
    int health = player->getHealth();

    for (int i = 0; i < hearts; ++i)
    {
        if (i + 1 <= health)
            this->guiRenderer->renderImage(i * healthSize, height - healthSize, healthSize, healthSize, TextureManager::getTexture("assets/textures/health.png"));
        else
            this->guiRenderer->renderImage(i * healthSize, height - healthSize, healthSize, healthSize, TextureManager::getTexture("assets/textures/health_empty.png"));
    }
    
    Screen::render();
}

bool GameScreen::handleClick(int x, int y) const
{
    if (!Screen::handleClick(x, y))
    {
        
    }
    return true;
}

void GameScreen::handleKeyPress(int key)
{
    
}
