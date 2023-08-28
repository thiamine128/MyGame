#include "Window.h"

#include "Game.h"
#include "Controller.h"
#include "ShaderManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

Window* Window::instance = nullptr;

Window::Window() {

}

void Window::init(int width, int height, const char* title)
{
    this->width = width;
    this->height = height;
    this->title = title;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create glfw window." << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(this->window);
    glfwSetFramebufferSizeCallback(this->window, framebufferSizeCallback);
    glfwSetKeyCallback(this->window, keyCallback);
    glfwSetMouseButtonCallback(this->window, mouseButtonCallback);
    glfwSetScrollCallback(this->window, scrollCallback);
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(this->window);
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(this->window);
}

void Window::pollEvents() const
{
    glfwPollEvents();
}

void Window::close() const
{
    glfwSetWindowShouldClose(this->window, true);
}

int Window::getKey(int key) const {
    return glfwGetKey(this->window, key);
}

void Window::onResize(int width, int height)
{
    this->width = width;
    this->height = height;
}

int Window::getWidth() const
{
    return this->width;
}

int Window::getHeight() const
{
    return this->height;
}

GLFWwindow *Window::getWindow() const
{
    return this->window;
}

Window *Window::getInstance()
{
    if (instance == nullptr) {
        instance = new Window();
    }
    return instance;
}

void Window::terminate()
{
    delete instance;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    Window::getInstance()->onResize(width, height);
    Game::getInstance()->getWorldRenderer()->updateProjection();
    Game::getInstance()->getGui()->updateViewport();
    ShaderManager::initUniforms(Game::getInstance()->getWorldRenderer(), Game::getInstance()->getGui());
}

void keyCallback(GLFWwindow* window, int key, int code, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        Game::getInstance()->getController()->onPress(key);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        Game::getInstance()->getController()->onMouseButtonPress(button, x, y);
    }
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    Game::getInstance()->getController()->onScroll(xOffset, yOffset);
}