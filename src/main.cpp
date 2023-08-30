#include <iostream>

#include "Game.h"

int main()
{
    Game::getInstance()->init();
    //开启主循环
    Game::getInstance()->run();
    Game::terminate();
    return 0;
}