#include "Game.h"

#include "TextureManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"
#include "Window.h"
#include "world/World.h"
#include "world/Items.h"
#include "Controller.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>

Game* Game::instance = nullptr;

Game::Game() : tickRate(0.05f) {
    
}

void Game::initRendering()
{
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to load glad." << std::endl;
    }
    TextureManager::initAtlas();
}

Game::~Game() {
    quitGame();
    delete this->renderer;
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


    initRendering();
    Item::init();
    
    renderer = new WorldRenderer();
    
    controller = new Controller();
    currentFrame = this->lastFrame = this->deltaTime = 0.0f;
    gui = new GuiRenderer();
    screenManager = new ScreenManager(this->gui);

    ShaderManager::initUniforms(this->renderer, this->gui);
    
    world = nullptr;
    screenManager->pushMenuScreen();
    paused = false;

    SoundManager::init();

    highestScore = readHighestScore();
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

        this->controller->processInput();

        bool pushFail = false;
        
        while (deltaTime > this->tickRate && this->world != nullptr && this->world->getPlayer()->getHealth() > 0) {
            deltaTime -= this->tickRate;

            if (!paused)
                this->world->tick();

            if (this->world->getPlayer()->getHealth() <= 0)
            {
                pushFail = true;
            }
        }

        ImGui::Begin("Debug");
        ImGui::Text("FPS: %d", this->fps);
        if (ImGui::Button("Spawn Items"))
        {
            if (world != nullptr)
            {
                world->getRoom()->spawnEntity(0, 1, 1.5, 1.5);
                world->getRoom()->spawnEntity(0, 2, 1.5, 2.5);
                world->getRoom()->spawnEntity(0, 3, 1.5, 3.5);
                world->getRoom()->spawnEntity(0, 4, 2.5, 1.5);
                world->getRoom()->spawnEntity(0, 5, 2.5, 2.5);
                world->getRoom()->spawnEntity(0, 6, 2.5, 3.5);
                world->getRoom()->spawnEntity(0, 7, 3.5, 1.5);
                world->getRoom()->spawnEntity(0, 8, 3.5, 2.5);
                world->getRoom()->spawnEntity(0, 9, 3.5, 3.5);
                world->getRoom()->spawnEntity(0, 10, 4.5, 1.5);
                world->getRoom()->spawnEntity(0, 11, 4.5, 2.5);
            }
        }
        if (ImGui::Button("Spawn Entrance"))
        {
                world->getRoom()->spawnEntity(3, 0, 0, 0);
        }
        ImGui::End();
        
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->screenManager->render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        Window::getInstance()->swapBuffers();
        Window::getInstance()->pollEvents();

        if (pushFail)
        {
            this->screenManager->pushFailedScreen();
        }

        SoundManager::update();
    }
}

WorldRenderer* Game::getWorldRenderer() const
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

GuiRenderer *Game::getGui() const
{
    return this->gui;
}

ScreenManager *Game::getScreenManager() const
{
    return this->screenManager;
}

float Game::getDeltaTime() const
{
    return this->deltaTime;
}

float Game::getFrameTime() const
{
    return this->currentFrame;
}

void Game::newGame()
{
    this->paused = false;
    if (this->world != nullptr)
    {
        delete this->world;
    }
    this->world = new World();
    this->renderer->setWorld(this->world);
}

void Game::startNewGame()
{
    this->newGame();
    this->screenManager->pushGameScreen();
}

void Game::pause()
{
    this->paused = true;
    this->screenManager->pushPauseScreen();
}

void Game::continueGame()
{
    this->paused = false;
    this->screenManager->popScreen();
}

void Game::quitGame()
{
    if (this->world != nullptr)
    {
        delete this->world;
    }
}

int Game::getHighestScore()
{
    return highestScore;
}

int Game::readHighestScore()
{
    std::ifstream sf("score.txt");
    int s = 0;
    sf >> s;
    sf.close();
    return s;
}

bool Game::updateScore(int score)
{
    int highest = readHighestScore();
    if (score > highest)
    {
        std::ofstream sf("score.txt");
        sf << score;
        sf.close();
        highest = score;
        return true;
    }
    return false;
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
    SoundManager::terminate();
    delete instance;
}
