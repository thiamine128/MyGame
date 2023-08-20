#pragma once

#include "world/World.h"
#include "Controller.h"
#include "rendering/GameRenderer.h"

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
    float fpsLastTime;
    int frameCnt;
    int fps;
    
    Game();

    static Game* instance;
};