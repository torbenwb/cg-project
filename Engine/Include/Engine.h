//
// Created by Torben Bernhard on 3/30/24.
//

#ifndef CG_PROJECT_ENGINE_H
#define CG_PROJECT_ENGINE_H

#include "Time.h"

class Engine
{
private:


protected:
    bool close = false;
    virtual void runStartupLogic();
    virtual void runAppLogic();
    virtual void runDisplayLogic();
    virtual void runCloseLogic();

public:
    void run();
};

#endif //CG_PROJECT_ENGINE_H
