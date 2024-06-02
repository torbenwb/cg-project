//
// Created by Torben Bernhard on 5/11/24.
//

#include "World.h"
#include "../noise/PerlinNoise.h"
#include <iostream>

namespace Voxel
{
    WorldSeed World::worldSeed = WorldSeed(25, 25, 25, 2, 2.25, 2.5, true);
    std::unordered_map<std::tuple<int, int, int>, unsigned short, World::TupleHash> World::deltas;
    std::vector<World::Delta> World::deltaList;

    unsigned short World::getVoxelType(int x, int y, int z) {

        unsigned short delta;
        if (getDelta(x, y, z, delta)) {
            return delta;
        }
        int waterLevel = 2;
        int sandLevel = 2;
        if (y < waterLevel){
            return VOXEL_TYPE_WATER;
        }

        const int xSeed = worldSeed.X;
        const int ySeed = worldSeed.Y;
        const int zSeed = worldSeed.Z;
        const int powSeed = worldSeed.POW;
        const double coefSeed = worldSeed.C1;
        const double coefSeed2 = worldSeed.C2;
        const double noiseY = worldSeed.N ? (double)y / ySeed : 0.0;
        double h = noise::PerlinNoise::getInstance().noise((double)x / xSeed, (double)z / zSeed, noiseY);

        h *= coefSeed;
        for(int i = 0; i < powSeed; i++) h *= h;
        h *= coefSeed2;

        if (y < h){
            if (y - waterLevel <= sandLevel) return VOXEL_TYPE_SAND;
            return VOXEL_TYPE_GRASS;
        }
        else {
            return VOXEL_TYPE_EMPTY;
        }
    }

    bool World::getVoxelEmpty(int x, int y, int z) {
        unsigned int voxelType = getVoxelType(x, y, z);
        return voxelType == VOXEL_TYPE_EMPTY;
    }

    unsigned short *** World::getChunk(glm::vec3 origin, int width, int height){
        unsigned short *** chunk = new unsigned short ** [width + 2];
        for(int x = 0; x < width + 2; x++){
            chunk[x] = new unsigned short *[width + 2];
            for(int z = 0; z < width + 2; z++){
                chunk[x][z] = new unsigned short [height + 2];
                for(int y = 0; y < height + 2; y++){
                    int a = origin.x + x + 1;
                    int b = origin.y + y + 1;
                    int c = origin.z + z + 1;
                    //printf("Get Chunk - x: %d, y: %d, z: %d. --> Coords: x: %d, y: %d, z: %d\n", x, y, z, a, b, c);
                    chunk[x][z][y] = getVoxelType(a, b, c);

                }
            }
        }
        return chunk;
    }

    void World::setVoxelType(int x, int y, int z, unsigned short voxelType) {
        deltas[{x, y, z}] = voxelType;
        deltaList.emplace_back(Delta(x, y, z, voxelType));
    }

    bool World::getDelta(int x, int y, int z, unsigned short & delta){
        std::tuple<int, int, int> key = {x ,y, z};
        if (deltas.find(key) != deltas.end()){
            delta = deltas[{x, y, z}];
            return true;
        }
        return false;
    }
}