//
// Created by Torben Bernhard on 3/30/24.
//

#ifndef CG_PROJECT_TIME_H
#define CG_PROJECT_TIME_H

#include <chrono>

class Time
{
private:
    static std::chrono::steady_clock::time_point startTime;
    static std::chrono::steady_clock::time_point lastUpdateTime;
    static float lastDeltaTime;

public:

    static void start();
    static void update();
    static float getDeltaTime();
};

#endif //CG_PROJECT_TIME_H
