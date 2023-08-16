#pragma once

#include "rendering/Camera.h"

class GameRenderer
{
public:
    GameRenderer();
    ~GameRenderer();

    void render() const;
    Camera* getCamera() const;
protected:
    Camera* camera;
};