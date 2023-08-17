#include "Game.h"

#include "TextureManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"

#include <GLFW/glfw3.h>

#include <iostream>

Game* Game::instance = nullptr;

Game::Game() : tickRate(0.05f) {
    
}

Game::~Game() {
    delete this->renderer;
    delete this->world;
    delete this->controller;
}

void Game::init() {
    Window::getInstance()->init(800, 600, "My Game");
    this->renderer = new GameRenderer();
    this->world = new World();
    this->controller = new Controller();
    this->currentFrame = this->lastFrame = this->deltaTime = 0.0f;
}

void Game::run() {
    while (!Window::getInstance()->shouldClose()) {
        this->currentFrame = static_cast<float>(glfwGetTime());
        this->deltaTime += currentFrame - lastFrame;
        this->lastFrame = currentFrame;
        this->processInput();

        while (deltaTime > this->tickRate) {
            deltaTime -= this->tickRate;
            this->world->tick();
        }

        this->renderer->render();

        Window::getInstance()->swapBuffers();
        Window::getInstance()->pollEvents();
    }
}

void Game::processInput() const {
    if (Window::getInstance()->getKey(GLFW_KEY_SPACE) == GLFW_PRESS)
        Window::getInstance()->close();
}

GameRenderer* Game::getGameRenderer() const
{
    return this->renderer;
}

Controller *Game::getController() const
{
    return this->controller;
}

World *Game::getWorld() const
{
    return this->world;
}

float Game::getDeltaTime() const
{
    return this->deltaTime;
}

float Game::getFrameTime() const
{
    return this->currentFrame;
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
    TextureManager::terminate();
    ModelManager::terminate();
    ShaderManager::terminate();
    delete instance;
}
