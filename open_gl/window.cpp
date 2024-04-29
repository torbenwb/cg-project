//
// Created by Torben Bernhard on 4/6/24.
//

#include "window.h"

namespace open_gl
{
    GLFWwindow* Window::window = nullptr;

    GLFWwindow* Window::initWindow() {
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

        window = glfwCreateWindow(width, height, title, NULL, NULL);

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
        window = initWindow();
    }

    void Window::update() {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void Window::close() {
        glfwDestroyWindow(window);
    }

    bool Window::getShouldClose() {
        return glfwWindowShouldClose(window);
    }

    GLFWwindow *Window::getWindow() {
        return window;
    }
}
