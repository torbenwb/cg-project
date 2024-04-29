//
// Created by Torben Bernhard on 3/30/24.
//

#include "Engine.h"

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