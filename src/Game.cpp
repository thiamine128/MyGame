#include "Game.h"

#include <GLFW/glfw3.h>

Game* Game::instance = nullptr;

Game::Game() {

}

Game::~Game() {
    delete this->renderer;
}

void Game::init() {
    Window::getInstance()->init(800, 600, "My Game");
    this->renderer = new GameRenderer();
}

void Game::run() {
    while (!Window::getInstance()->shouldClose()) {
        this->processInput();

        this->renderer->render();

        Window::getInstance()->swapBuffers();
        Window::getInstance()->pollEvents();
    }
}

void Game::processInput() const {
    if (Window::getInstance()->getKey(GLFW_KEY_SPACE) == GLFW_PRESS)
        Window::getInstance()->close();
}

Game* Game::getInstance() {
    if (instance == nullptr) {
        instance = new Game();
    }
    return instance;
}

void Game::terminate()
{
    Window::terminate();
    delete instance;
}
