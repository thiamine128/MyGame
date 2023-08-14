#pragma once

class GLFWwindow;

void framebufferSizeCallback(GLFWwindow*, int, int);

class Window
{
public:
    Window(int, int, const char*);
    ~Window();

    bool shouldClose() const;
    void pollEvents() const;
    void swapBuffers() const;
    void close() const;
    int getKey(int) const;
protected:
    int width, height;
    const char* title;
    GLFWwindow* window;
};