//
// Created by Torben Bernhard on 4/26/24.
//

#ifndef CG_PROJECT_PERLINNOISE_H
#define CG_PROJECT_PERLINNOISE_H

#include <vector>

/*
 * Credit to Solarion Programmer block post:
 * https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/
 * https://github.com/sol-prog/Perlin_Noise
 */

namespace noise
{
    class PerlinNoise {
        // The permutation vector
        std::vector<int> p;
        // Initialize with the reference values for the permutation vector
        PerlinNoise();
        // Generate a new permutation vector based on the value of seed
        PerlinNoise(unsigned int seed);

    public:
        static PerlinNoise& getInstance(){
            static PerlinNoise instance;
            return instance;
        }
        // Get a noise value, for 2D images z can have any value
        double noise(double x, double y, double z);
    private:
        double fade(double t);
        double lerp(double t, double a, double b);
        double grad(int hash, double x, double y, double z);
    };

}


#endif //CG_PROJECT_PERLINNOISE_H
