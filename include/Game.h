#pragma once

#include <Window.h>
#include <GameRenderer.h>

class Game
{
public:
    Game();
    ~Game();

    void run();
    void processInput() const;
protected:
    Window* window;
    GameRenderer* renderer;
};