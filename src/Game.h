#pragma once

#include "Window.h"
#include "world/World.h"
#include "rendering/GameRenderer.h"
#include "Controller.h"

class Game
{
public:
    const float tickRate;

    ~Game();

    void init();
    void run();
    void processInput() const;
    GameRenderer* getGameRenderer() const;
    Controller* getController() const;
    World* getWorld() const;
    float getDeltaTime() const;
    float getFrameTime() const;

    static Game* getInstance();
    static void terminate();
protected:
    World* world;
    GameRenderer* renderer;
    Controller* controller;
    float currentFrame, lastFrame, deltaTime;
    
    Game();

    static Game* instance;
};