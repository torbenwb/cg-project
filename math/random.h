//
// Created by Torben Bernhard on 4/8/24.
//

#ifndef CG_PROJECT_RANDOM_H
#define CG_PROJECT_RANDOM_H
#include <random>

namespace math
{
    class Random
    {
    public:
        static float randRange(float min, float max)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dis(min, max);
            return dis(gen);
        }
    };
}

#endif //CG_PROJECT_RANDOM_H
