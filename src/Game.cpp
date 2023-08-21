#include "Game.h"

#include "TextureManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "Window.h"
#include "world/World.h"
#include "rendering/GameRenderer.h"
#include "Controller.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui_ImplGlfw_InitForOpenGL(Window::getInstance()->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");


    this->renderer = new GameRenderer();
    this->world = new World();
    this->controller = new Controller();
    this->currentFrame = this->lastFrame = this->deltaTime = 0.0f;
}

void Game::run() {
    this->frameCnt = this->fps = 0;
    while (!Window::getInstance()->shouldClose()) {
        this->currentFrame = static_cast<float>(glfwGetTime());
        this->deltaTime += currentFrame - lastFrame;
        this->lastFrame = currentFrame;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ++frameCnt;
        if (this->currentFrame - this->fpsLastTime >= 1.0) {
            
            this->fps = this->frameCnt;
            this->fpsLastTime = this->currentFrame;
            this->frameCnt = 0;
        }

        this->processInput();
        while (deltaTime > this->tickRate) {
            deltaTime -= this->tickRate;
            this->world->tick();
        }

        ImGui::Begin("Debug");
        ImGui::Text("FPS: %d", this->fps);
        if (ImGui::Button("nextDay"))
        {
            this->world->nextDay();
        }
        for (int i = 0; i < INV_SIZE; ++i) {
            ItemStack const& is = this->world->getPlayer()->getSlot(i);
            ImGui::Text("%s : %d", is.item == nullptr ? "None" : is.item->getName().c_str(), is.cnt);
        }
        ImGui::End();
        
        this->renderer->render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    delete instance;
}
