#include <iostream>

#include "Game.h"

int main()
{
    Game::getInstance()->init();
    Game::getInstance()->run();
    Game::terminate();
    return 0;
}