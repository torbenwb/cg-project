//
// Created by Torben Bernhard on 4/6/24.
//

#ifndef CG_PROJECT_WINDOW_H
#define CG_PROJECT_WINDOW_H

#include "glad.h"
#include "glfw3.h"

namespace open_gl
{

    class Window {
    private:
        const char* DEFAULT_TITLE = "Default Window Title";
        const int DEFAULT_WIDTH = 500;
        const int DEFAULT_HEIGHT = 500;
        static GLFWwindow* window;
        int width, height;
        const char* title;
        GLFWwindow* initWindow();
    public:
        Window()
        {
            this->title = DEFAULT_TITLE;
            this->width = DEFAULT_WIDTH;
            this->height = DEFAULT_HEIGHT;
        }

        Window(int width, int height, const char* title)
        {
            this->title = title;
            this->width = width;
            this->height = height;
        }

        void open();
        void update();
        void close();
        bool getShouldClose();

        static GLFWwindow* getWindow();
    };
}




#endif //CG_PROJECT_WINDOW_H
