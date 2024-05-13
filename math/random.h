//
// Created by Torben Bernhard on 4/8/24.
//

#ifndef CG_PROJECT_RANDOM_H
#define CG_PROJECT_RANDOM_H
#include <random>

namespace math
{
    namespace random
    {
        double randomDouble(double min, double max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<double> dis(min, max);
            return dis(gen);
        }

        int randomInt(int min, int max){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis(min, max);
            return dis(gen);
        }
    };
}

#endif //CG_PROJECT_RANDOM_H
