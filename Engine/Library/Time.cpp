//
// Created by Torben Bernhard on 3/30/24.
//

#include "../Include/Time.h"

// Define and initialize the static member variables
std::chrono::steady_clock::time_point Time::startTime;
std::chrono::steady_clock::time_point Time::lastUpdateTime;
float Time::lastDeltaTime = 0.0f; // Initialize lastDeltaTime

void Time::start()
{
    Time::startTime = std::chrono::steady_clock::now();
    Time::lastUpdateTime = Time::startTime;
}

void Time::update() {
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> durationSinceLastUpdate = currentTime - Time::lastUpdateTime;
    Time::lastDeltaTime = durationSinceLastUpdate.count();
    Time::lastUpdateTime = currentTime;
}

float Time::getDeltaTime() {
    return Time::lastDeltaTime;
}