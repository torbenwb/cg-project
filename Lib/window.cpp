//
// Created by Torben Bernhard on 3/26/24.
//

#include "window.h"
#include <iostream>


GLFWwindow* initWindow(int x, int y, int width, int height, const char* title)
{
    if (!glfwInit())
    {
        std::cout << "Failed to Init GLFW" << std::endl;
        return NULL;
    }

    #ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Window is Null" << std::endl;
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return NULL;
    }

    return  window;
}