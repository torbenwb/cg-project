//
// Created by Torben Bernhard on 3/30/24.
//

#include "../Include/Engine.h"
#include "glad.h" // GL header file
#include <GLFW/glfw3.h>       // GL toolkit
#include <stdio.h>			// printf, etc
#include "window.h"
#include "GraphicsLayer.h"
#include <glm/glm.hpp>

void Engine::run() {
    runStartupLogic();
    while (!close)
    {
        runAppLogic();
        runDisplayLogic();
    }
    runCloseLogic();
}

void Engine::runStartupLogic() {

}

void Engine::runAppLogic() {

}

void Engine::runDisplayLogic() {

}

void Engine::runCloseLogic() {

}