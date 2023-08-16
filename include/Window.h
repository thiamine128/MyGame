#pragma once

class GLFWwindow;

void framebufferSizeCallback(GLFWwindow*, int, int);

class Window
{
public:
    ~Window();

    void init(int, int, const char*);
    bool shouldClose() const;
    void pollEvents() const;
    void swapBuffers() const;
    void close() const;
    int getKey(int) const;
    void onResize(int, int);
    int getWidth() const;
    int getHeight() const;

    static Window* getInstance();
    static void terminate();
protected:
    int width, height;
    const char* title;
    GLFWwindow* window;

    Window();

    static Window* instance;
};