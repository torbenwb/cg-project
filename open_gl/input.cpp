//
// Created by Torben Bernhard on 4/8/24.
//

#include "input.h"
#include "window.h"
#include <iostream>

namespace open_gl
{
    double Input::lastCursorPositionX = 0.0;
    double Input::lastCursorPositionY = 0.0;
    float Input::mouseX = 0.0f;
    float Input::mouseY = 0.0f;
    bool Input::windowFocus = true;
    bool Input::cursorFocus = true;

    bool Input::getKey(int key) {
        if (!windowFocus) return false;
        GLFWwindow* window = Window::getWindow();
        if (window == NULL) return false;
        return glfwGetKey(window, key);
    }

    float Input::getAxis(int positiveKey, int negativeKey) {
        if (!windowFocus) return 0.0f;
        float output = 0.0f;
        if (getKey(positiveKey)) output += 1.0f;
        if (getKey(negativeKey)) output -= 1.0f;
        return output;
    }

    void Input::registerCallbacks() {
        GLFWwindow* window = Window::getWindow();
        if (window == nullptr) return;

        glfwSetCursorPosCallback(window, cursorPositionCallback);
        glfwSetCursorEnterCallback(window, cursorEnterExitCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
    }

    void Input::cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {

    }

    void Input::disableCursor() {
        GLFWwindow* window = Window::getWindow();
        if (window == nullptr) return;
        windowFocus = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void Input::enableCursor() {
        GLFWwindow* window = Window::getWindow();
        if (window == nullptr) return;
        windowFocus = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    float Input::getMouseX() {
        GLFWwindow* window = Window::getWindow();
        if (window == nullptr) return 0.0f;
        if (!windowFocus) return 0.0;
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        float mX = xPos - lastCursorPositionX;
        lastCursorPositionX = xPos;
        return mX;
    }

    float Input::getMouseY() {
        GLFWwindow* window = Window::getWindow();
        if (window == nullptr) return 0.0f;
        if (!windowFocus) return 0.0;
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        float mY = yPos - lastCursorPositionY;
        lastCursorPositionY = yPos;
        return mY;
    }

    void Input::cursorEnterExitCallback(GLFWwindow *window, int entered) {
        if (entered) cursorFocus = true;
        else cursorFocus = false;
    }

    void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            if (cursorFocus) disableCursor();
        }

    }
}

