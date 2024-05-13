//
// Created by Torben Bernhard on 5/11/24.
//

#ifndef CG_PROJECT_WORLD_H
#define CG_PROJECT_WORLD_H

#include <glm/glm.hpp>

namespace Voxel
{
    struct WorldSeed
    {
        int X = 25;
        int Y = 25;
        int Z = 25;
        int POW = 2;
        double C1 = 2.25;
        double C2 = 2.5;
        bool N = true;

        WorldSeed(){}
        WorldSeed(int x, int y, int z, int pow, double c1, double c2, bool n):
            X(x), Y(y), Z(z), POW(pow), C1(c1), C2(c2), N(n){}
        WorldSeed(const WorldSeed& other):
            X(other.X), Y(other.Y), Z(other.Z), POW(other.POW), C1(other.C1), C2(other.C2), N(other.N){}
        WorldSeed& operator=(const WorldSeed& other)
        {
            if (this != &other)
            {
                X = other.X;
                Y = other.Y;
                Z = other.Z;
                POW = other.POW;
                C1 = other.C1;
                C2 = other.C2;
                N = other.N;
            }
            return *this;
        }
    };

    class World {
    public:
        static const unsigned short VOXEL_TYPE_NULL = 0;
        static const unsigned short VOXEL_TYPE_EMPTY = 1;
        static const unsigned short VOXEL_TYPE_GRASS = 2;
        static const unsigned short VOXEL_TYPE_WATER = 3;
        static const unsigned short VOXEL_TYPE_SAND = 4;

        static unsigned short getVoxelType(int x, int y, int z);
        static bool getVoxelEmpty(int x, int y, int z);
        static WorldSeed worldSeed;

        static unsigned short *** getChunk(glm::vec3 origin, int width, int height);

        // Todo
        /*
         * Load Chunk -
         * - if chunk data is already in cache do nothing
         * - if chunk data is not in cache load chunk into cache
         * - if chunk data has changed reload chunk data into cache
         * - when client calls get voxel type pull data from chunk in cache
         * - when client calls get voxel type if chunk data is not in cache
         * - load all chunk data into cache?
         *
         * When loading chunk - also cache other chunk relevant data:
         * - subdivide into octree for collision / raycasts
         */
    };
}



#endif //CG_PROJECT_WORLD_H
