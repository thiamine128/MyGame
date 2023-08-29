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
    this->screenType = 1;
    this->shouldRenderMap = false;
}

void GameScreen::render() const
{
    if (Game::getInstance()->getScreenManager()->inGameScreen())
        this->worldRenderer->render();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    this->guiRenderer->renderPost(this->worldRenderer);

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

    this->guiRenderer->renderTextCentered(Window::getInstance()->getWidth() / 2, height - 80, 1.0f, "Score: " + std::to_string(worldRenderer->getWorld()->getScore()));
    
    Screen::render();
    renderItemHint();
    if (shouldRenderMap)
        renderMap(height / 3 * 2, 0.8f);
    glEnable(GL_DEPTH_TEST);
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
    if (key == GLFW_KEY_ESCAPE)
    {
        Game::getInstance()->pause();
    }
    if (key == GLFW_KEY_M)
    {
        shouldRenderMap = !shouldRenderMap;
    }
}

void GameScreen::renderMap(int size, float alpha) const
{
    int w = Window::getInstance()->getWidth(), h = Window::getInstance()->getHeight();
    guiRenderer->renderRect(w / 2 - size / 2, h / 2 - size / 2, w / 2 + size / 2, h / 2 + size / 2, glm::vec4(0.5, 0.5, 0.5, alpha));
    int roomSize = size / 13;
    for (int i = 0; i < 13; ++i)
    {
        for (int j = 0; j < 13; ++j)
        {
            World* world = worldRenderer->getWorld();
            if (world->getRoom(12 - i, j) != nullptr)
            {
                Room* room = world->getRoom(12 - i, j);
                glm::vec4 color = glm::vec4(0.6, 0.6, 0.6, 1.0);
                if (room == world->getRoom())
                    color = glm::vec4(0.8, 0.8, 0.8, 1.0);
                if (room->isBossRoom())
                    color.r = 1.0f;
                if (room->isItemRoom())
                    color.r = 1.0, color.g = 1.0;
                guiRenderer->renderRect(w / 2 - size / 2 + i * roomSize + 5, h / 2 - size / 2 + j * roomSize + 5, w / 2 - size / 2 + (i + 1) * roomSize - 5, h / 2 - size / 2 + (j + 1) * roomSize - 5, color);
            }
        }
    }
}

void GameScreen::renderItemHint() const
{
    Item* item = worldRenderer->getWorld()->getRoom()->getNearestItem();
    int height = Window::getInstance()->getHeight();
    if (item != nullptr)
    {
        guiRenderer->renderText(10, height / 8 * 7, 1.0f, item->getName());
        auto desc = item->getDescription();
        for (int i = 0; i < desc.size(); ++i)
            guiRenderer->renderText(10, height / 8 * (6 - i), 1.0f, "-" + desc[i]);
    }
}
