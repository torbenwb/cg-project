//
// Created by Torben Bernhard on 4/1/24.
//

#include "../Include/Window.h"

GLFWwindow* Window::initWindow(int x, int y, int width, int height, const char* title)
{
    if (!glfwInit())
    {
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
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return NULL;
    }

    return  window;
}

void Window::open() {
    window = initWindow(0, 0, this->width, this->height, this->title);
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::close(){
    glfwDestroyWindow(window);
}

bool Window::getKey(int button) {
    return glfwGetKey(window, button);
}