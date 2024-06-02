//
// Created by Torben Bernhard on 4/8/24.
//

#ifndef CG_PROJECT_INPUT_H
#define CG_PROJECT_INPUT_H

#include "glad.h"
#include "glfw3.h"

namespace open_gl
{
    class Input {
    private:
        static double lastCursorPositionX;
        static double lastCursorPositionY;
        static float mouseX;
        static float mouseY;
        static bool windowFocus;
        static bool cursorFocus;

        static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
        static void cursorEnterExitCallback(GLFWwindow* window, int entered);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    public:
        static bool getKey(int key);
        static float getAxis(int positiveKey, int negativeKey);
        static void registerCallbacks();
        static void disableCursor();
        static void enableCursor();
        static float getMouseX();
        static float getMouseY();
        static bool getMouseLeft();
        static bool getMouseRight();
    };
}



#endif //CG_PROJECT_INPUT_H
