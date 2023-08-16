#pragma once

#include "Window.h"
#include "rendering/GameRenderer.h"

class Game
{
public:
    ~Game();

    void init();
    void run();
    void processInput() const;

    static Game* getInstance();
    static void terminate();
protected:
    GameRenderer* renderer;
    Game();

    static Game* instance;
};