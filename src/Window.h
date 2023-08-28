#pragma once

class GLFWwindow;

void framebufferSizeCallback(GLFWwindow*, int, int);
void keyCallback(GLFWwindow*, int, int, int, int);
void mouseButtonCallback(GLFWwindow*, int, int, int);
void scrollCallback(GLFWwindow*, double, double);
void cursorPosCallback(GLFWwindow*, double, double);
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
    GLFWwindow* getWindow() const;

    static Window* getInstance();
    static void terminate();
protected:
    int width, height;
    const char* title;
    GLFWwindow* window;

    Window();

    static Window* instance;
};