#include "Game.h"

#include <GLFW/glfw3.h>

Game::Game() {
    this->window = new Window(800, 600, "My Game");
    this->renderer = new GameRenderer();
}

Game::~Game() {
    delete this->window;
    delete this->renderer;
}

void Game::run() {
    while (!window->shouldClose()) {
        this->processInput();

        this->renderer->render();

        this->window->swapBuffers();
        this->window->pollEvents();
    }
}

void Game::processInput() const {
    if (this->window->getKey(GLFW_KEY_SPACE) == GLFW_PRESS)
        this->window->close();
}