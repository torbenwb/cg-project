//
// Created by Torben Bernhard on 4/1/24.
//

#ifndef CG_PROJECT_WINDOW_H
#define CG_PROJECT_WINDOW_H

#include "glad.h"
#include "glfw3.h"

class Window
{
private:
    GLFWwindow* window;
    int width, height;
    const char* title;

    GLFWwindow* initWindow(int x, int y, int width, int height, const char* title);


public:
    Window()
    {
        this->title = "Default Window";
        this->width = 500;
        this->height = 500;
    }

    Window(int width, int height, const char* title)
    {
        this->title = title;
        this->width = width;
        this->height = height;
    }


    bool getShouldClose() {
        return glfwWindowShouldClose(window);
    }

    void open();
    void update();
    void close();
    bool getKey(int button);
};

#endif //CG_PROJECT_WINDOW_H
