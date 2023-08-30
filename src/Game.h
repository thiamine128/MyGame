#pragma once

#include "world/World.h"
#include "Controller.h"
#include "rendering/WorldRenderer.h"
#include "rendering/GuiRenderer.h"
#include "ui/ScreenManager.h"

class Game
{
public:
    const float tickRate;

    ~Game();

    void init();
    void run();
    
    WorldRenderer* getWorldRenderer() const;
    Controller* getController() const;
    World* getWorld() const;
    GuiRenderer* getGui() const;
    ScreenManager* getScreenManager() const;
    float getDeltaTime() const;
    float getFrameTime() const;
    void newGame();
    void startNewGame();
    void pause();
    void continueGame();
    void quitGame();
    int getHighestScore();
    int readHighestScore();
    bool updateScore(int);

    static Game* getInstance();
    static void terminate();
protected:
    World* world;
    GuiRenderer* gui;
    WorldRenderer* renderer;
    Controller* controller;
    ScreenManager* screenManager;
    float currentFrame, lastFrame, deltaTime;
    float fpsLastTime;
    int frameCnt;
    int fps;
    int highestScore;
    bool paused;
    
    Game();

    void initRendering();

    static Game* instance;
};