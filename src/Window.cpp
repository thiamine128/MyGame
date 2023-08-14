#include <Window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

Window::Window(int width, int height, const char* title)
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

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
