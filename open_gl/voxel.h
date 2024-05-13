//
// Created by Torben Bernhard on 4/15/24.
//

#ifndef CG_PROJECT_VOXEL_H
#define CG_PROJECT_VOXEL_H

#include <vector>
#include <tuple>
#include <unordered_map>
#include <glm/glm.hpp>
#include "mesh.h"
#include "../noise/PerlinNoise.h"
#include "../texture_images/atlas.h"
#include <iostream>
#include <random>
#include <cmath>
#include "scene.h"

namespace open_gl
{
    static const int CHUNK_WIDTH = 32;
    static const int CHUNK_HEIGHT = 128;

    static const unsigned short VOXEL_TYPE_NULL = 0;
    static const unsigned short VOXEL_TYPE_EMPTY = 1;
    static const unsigned short VOXEL_TYPE_GRASS = 2;
    static const unsigned short VOXEL_TYPE_WATER = 3;

    class seed_function{
    public:
        static int seedCalls;
        unsigned short getVoxelTypeGlobal(int x, int y, int z)
        {
            seed_function::seedCalls += 1;
            if (y <= 1){
                return VOXEL_TYPE_WATER;
            }
            const int xSeed = 25;
            const int ySeed = 5;
            const int zSeed = 25;
            const int powSeed = 3;
            const double coefSeed = 2.0;
            const double coefSeed2 = 2.5;
            double h = noise::PerlinNoise::getInstance().noise((double)x / xSeed, (double)z / zSeed, 0.0);

            h *= coefSeed;
            for(int i = 0; i < powSeed; i++) h *= h;
            h *= coefSeed2;

            if (y < h){
                return VOXEL_TYPE_GRASS;
            }
            else {
                return VOXEL_TYPE_EMPTY;
            }
        }
    };

    int seed_function::seedCalls = 0;

    class voxelCache
    {
    private:
        seed_function seedFunction;
        unsigned short*** cache;
        int width, height;

    public:
        int cacheSuccess = 0;
        voxelCache(int width, int height)
        {
            width += 2; height += 2;
            this->width = width;
            this->height = height;
            cache = new unsigned short ** [width];
            for(int x = 0; x < width; x++){
                cache[x] = new unsigned short *[width];
                for(int z = 0; z < width; z++){
                    cache[x][z] = new unsigned short [height];
                    for(int y = 0; y < height; y++){
                        cache[x][z][y] = VOXEL_TYPE_NULL;
                    }
                }
            }
        }
        ~voxelCache(){
            for(int i = 0; i < width; i++){
                for(int j = 0; j < width; j++){
                    delete[] cache[i][j];
                }
                delete[] cache[i];
            }
            delete[] cache;
        }
        unsigned short getVoxelType(int originX, int originY, int originZ, int x, int y, int z);
    };



    unsigned short voxelCache::getVoxelType(int originX, int originY, int originZ, int x, int y, int z) {
        if (cache[x + 1][z + 1][y + 1] != VOXEL_TYPE_NULL) return cache[x + 1][z + 1][y + 1];

        unsigned short voxelType = seedFunction.getVoxelTypeGlobal(originX + x, originY + y, originZ + z);
        cache[x + 1][z + 1][y + 1] = voxelType;

        return voxelType;
    }

    class voxel
    {
    public:
        static const char TOP_FACE = 0;
        static const char BOTTOM_FACE = 1;
        static const char LEFT_FACE = 2;
        static const char RIGHT_FACE = 3;
        static const char BACK_FACE = 4;
        static const char FRONT_FACE = 5;

        static void getChunkOrigin(glm::vec3 worldPosition, int& x, int& y, int& z);

        constexpr static const float faceSize = 0.5f;

        static void getFaceUVs(const char face, const uint voxelType, std::vector<glm::vec2>& uvs);

        static void topFace(uint voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs);
        static void bottomFace(uint voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs);
        static void leftFace(uint voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs);
        static void rightFace(uint voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs);
        static void backFace(uint voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs);
        static void frontFace(uint voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs);

        static Mesh* toMesh(std::vector<glm::vec3> vertices, std::vector<int> indices, std::vector<glm::vec2> uvs);
        static Mesh* generateChunkMesh(int xOrigin = 0, int zOrigin = 0);
        static void generateChunk(glm::vec3 origin,
                                  std::vector<glm::vec3>& vertices,
                                  std::vector<glm::vec2>& uvs,
                                  std::vector<int>& triIndices);
        static uint getVoxelType(int x, int y, int z, voxelCache& cache);
        static double randomDouble(double min, double max);
        static int randomInt(int min, int max);

        static glm::vec3 getChunkOrigin(glm::vec3 worldPosition);
    };

    Mesh* voxel::toMesh(std::vector<glm::vec3> vertices, std::vector<int> indices, std::vector<glm::vec2> uvs) {
        Mesh* newMesh = new Mesh();
        newMesh->setVertices(vertices);
        newMesh->setTriIndices(indices);
        newMesh->setUVs(uvs);
        newMesh->recalculateNormals();
        newMesh->buffer();
        return newMesh;
    }

    void voxel::topFace(uint voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs) {
        int startIndex = vertices.size();
        vertices.emplace_back(offset + glm::vec3(-faceSize, faceSize, -faceSize));
        vertices.emplace_back(offset + glm::vec3(faceSize, faceSize, -faceSize));
        vertices.emplace_back(offset + glm::vec3(-faceSize, faceSize, faceSize));
        vertices.emplace_back(offset + glm::vec3(faceSize, faceSize, faceSize));

        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 0);
        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 3);
        indices.emplace_back(startIndex + 1);

        getFaceUVs(TOP_FACE, voxelType, uvs);
    }

    void voxel::bottomFace(uint voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs) {
        int startIndex = vertices.size();
        vertices.emplace_back(offset + glm::vec3(-faceSize, -faceSize, -faceSize));
        vertices.emplace_back(offset + glm::vec3(faceSize, -faceSize, -faceSize));
        vertices.emplace_back(offset + glm::vec3(-faceSize, -faceSize, faceSize));
        vertices.emplace_back(offset + glm::vec3(faceSize, -faceSize, faceSize));

        indices.emplace_back(startIndex + 0);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 3);
        indices.emplace_back(startIndex + 2);

        getFaceUVs(BOTTOM_FACE, voxelType, uvs);
    }

    void voxel::leftFace(uint voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs) {
        int startIndex = vertices.size();
        vertices.emplace_back(offset + glm::vec3(-faceSize, faceSize, -faceSize));
        vertices.emplace_back(offset + glm::vec3(-faceSize, faceSize, faceSize));
        vertices.emplace_back(offset + glm::vec3(-faceSize, -faceSize, -faceSize));
        vertices.emplace_back(offset + glm::vec3(-faceSize, -faceSize, faceSize));

        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 0);
        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 3);
        indices.emplace_back(startIndex + 1);

        getFaceUVs(LEFT_FACE, voxelType, uvs);
    }

    void voxel::rightFace(uint voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs) {
        int startIndex = vertices.size();
        vertices.emplace_back(offset + glm::vec3(faceSize, faceSize, -faceSize));
        vertices.emplace_back(offset + glm::vec3(faceSize, faceSize, faceSize));
        vertices.emplace_back(offset + glm::vec3(faceSize, -faceSize, -faceSize));
        vertices.emplace_back(offset + glm::vec3(faceSize, -faceSize, faceSize));

        indices.emplace_back(startIndex + 0);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 3);
        indices.emplace_back(startIndex + 2);

        getFaceUVs(RIGHT_FACE, voxelType, uvs);
    }

    void voxel::backFace(uint voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs) {
        int startIndex = vertices.size();
        vertices.emplace_back(offset + glm::vec3(-faceSize, faceSize, faceSize));
        vertices.emplace_back(offset + glm::vec3(faceSize, faceSize, faceSize));
        vertices.emplace_back(offset + glm::vec3(-faceSize, -faceSize, faceSize));
        vertices.emplace_back(offset + glm::vec3(faceSize, -faceSize, faceSize));

        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 0);
        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 3);
        indices.emplace_back(startIndex + 1);

        getFaceUVs(BACK_FACE, voxelType, uvs);
    }

    void voxel::frontFace(uint voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs) {
        int startIndex = vertices.size();
        vertices.emplace_back(offset + glm::vec3(-faceSize, faceSize, -faceSize));
        vertices.emplace_back(offset + glm::vec3(faceSize, faceSize, -faceSize));
        vertices.emplace_back(offset + glm::vec3(-faceSize, -faceSize, -faceSize));
        vertices.emplace_back(offset + glm::vec3(faceSize, -faceSize, -faceSize));

        indices.emplace_back(startIndex + 0);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 3);
        indices.emplace_back(startIndex + 2);

        getFaceUVs(FRONT_FACE, voxelType, uvs);
    }



    /*
     * Generate chunk mesh
     */
    Mesh* voxel::generateChunkMesh(int xOrigin, int zOrigin) {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<int> indices;

        voxelCache cache(CHUNK_WIDTH, CHUNK_HEIGHT);

        for(int x = 0; x < CHUNK_WIDTH; x++)
        {
            for(int z = 0; z < CHUNK_WIDTH; z++)
            {
                for(int y = 0; y < CHUNK_HEIGHT; y++)
                {
                    int globalX = xOrigin + x;
                    int globalY = y;
                    int globalZ = zOrigin + z;
                    uint voxelType = cache.getVoxelType(xOrigin, 0, zOrigin, x, y, z);


                    // If this voxel is empty then ignore and move to the next
                    if (voxelType == VOXEL_TYPE_EMPTY) continue;

                    // The space above this voxel is empty
                    if (cache.getVoxelType(xOrigin, 0, zOrigin, x, y + 1, z) == VOXEL_TYPE_EMPTY)
                    {
                        topFace(voxelType, glm::vec3(x, y, z), vertices, indices, uvs);
                    }
                    // The space below this voxel is empty
                    if (cache.getVoxelType(xOrigin, 0, zOrigin, x, y - 1, z) == VOXEL_TYPE_EMPTY)
                    {
                        bottomFace(voxelType, glm::vec3(x, y, z), vertices, indices, uvs);
                    }
                    // The space to the right of this voxel is empty
                    if (cache.getVoxelType(xOrigin, 0, zOrigin, x + 1, y, z) == VOXEL_TYPE_EMPTY)
                    {
                        rightFace(voxelType, glm::vec3(x, y, z), vertices, indices, uvs);
                    }
                    // The space to the left of this voxel is empty
                    if (cache.getVoxelType(xOrigin, 0, zOrigin, x - 1, y, z) == VOXEL_TYPE_EMPTY)
                    {
                        leftFace(voxelType, glm::vec3(x, y, z), vertices, indices, uvs);
                    }
                    // The space behind of this voxel is empty
                    if (cache.getVoxelType(xOrigin, 0, zOrigin, x, y, z + 1) == VOXEL_TYPE_EMPTY)
                    {
                        backFace(voxelType, glm::vec3(x, y, z), vertices, indices, uvs);
                    }
                    // The space in front of this voxel is empty
                    if (cache.getVoxelType(xOrigin, 0, zOrigin, x, y, z - 1) == VOXEL_TYPE_EMPTY)
                    {
                        frontFace(voxelType, glm::vec3(x, y, z), vertices, indices, uvs);
                    }
                }
            }
        }


        return toMesh(vertices, indices, uvs);
    }

    void voxel::getFaceUVs(const char face, const uint voxelType, std::vector<glm::vec2>& uvs) {
        if (voxelType == VOXEL_TYPE_WATER){
            texture_images::atlas::getUVs(0, 0, 2, 2, uvs);
            return;
        }
        if (face == TOP_FACE) texture_images::atlas::getUVs(0, 1, 2, 2, uvs);
        else if (face == LEFT_FACE) texture_images::atlas::getUVs(1, 1, 2, 2, uvs, 1);
        else if (face == RIGHT_FACE) texture_images::atlas::getUVs(1, 1, 2, 2, uvs, 1);
        else if (face == FRONT_FACE) texture_images::atlas::getUVs(1, 1, 2, 2, uvs, 1);
        else if (face == BACK_FACE) texture_images::atlas::getUVs(1, 1, 2, 2, uvs, 1);
        else texture_images::atlas::getUVs(1, 1, 2, 2, uvs);
        return;

    }

    double voxel::randomDouble(double min, double max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(min, max);
        return dis(gen);
    }

    int voxel::randomInt(int min, int max){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(min, max);
        return dis(gen);
    }

    void voxel::getChunkOrigin(glm::vec3 worldPosition, int &x, int &y, int &z) {
        int globalX = worldPosition.x;
        int globalY = worldPosition.y;
        int globalZ = worldPosition.z;
        x = globalX >= 0 ? (globalX / CHUNK_WIDTH) * CHUNK_WIDTH : ((globalX / CHUNK_WIDTH) - 1) * CHUNK_WIDTH;
        y = (globalY / CHUNK_HEIGHT) * CHUNK_HEIGHT;
        z = globalZ >= 0 ? (globalZ / CHUNK_WIDTH) * CHUNK_WIDTH : ((globalZ / CHUNK_WIDTH) - 1) * CHUNK_WIDTH;
        x = -x - CHUNK_WIDTH;
        y = 0;
        z = -z - CHUNK_WIDTH;
    }

    void voxel::generateChunk(glm::vec3 origin,
                              std::vector<glm::vec3>& vertices,
                              std::vector<glm::vec2>& uvs,
                              std::vector<int>& triIndices)
    {
        voxelCache cache(CHUNK_WIDTH, CHUNK_HEIGHT);
        int xOrigin = (int)origin.x;
        int zOrigin = (int)origin.z;

        for(int x = 0; x < CHUNK_WIDTH; x++)
        {
            for(int z = 0; z < CHUNK_WIDTH; z++)
            {
                for(int y = 0; y < CHUNK_HEIGHT; y++)
                {
                    int globalX = xOrigin + x;
                    int globalY = y;
                    int globalZ = zOrigin + z;
                    uint voxelType = cache.getVoxelType(xOrigin, 0, zOrigin, x, y, z);


                    // If this voxel is empty then ignore and move to the next
                    if (voxelType == VOXEL_TYPE_EMPTY) continue;

                    // The space above this voxel is empty
                    if (cache.getVoxelType(xOrigin, 0, zOrigin, x, y + 1, z) == VOXEL_TYPE_EMPTY)
                    {
                        topFace(voxelType, glm::vec3(x, y, z), vertices, triIndices, uvs);
                    }
                    // The space below this voxel is empty
                    if (cache.getVoxelType(xOrigin, 0, zOrigin, x, y - 1, z) == VOXEL_TYPE_EMPTY)
                    {
                        bottomFace(voxelType, glm::vec3(x, y, z), vertices, triIndices, uvs);
                    }
                    // The space to the right of this voxel is empty
                    if (cache.getVoxelType(xOrigin, 0, zOrigin, x + 1, y, z) == VOXEL_TYPE_EMPTY)
                    {
                        rightFace(voxelType, glm::vec3(x, y, z), vertices, triIndices, uvs);
                    }
                    // The space to the left of this voxel is empty
                    if (cache.getVoxelType(xOrigin, 0, zOrigin, x - 1, y, z) == VOXEL_TYPE_EMPTY)
                    {
                        leftFace(voxelType, glm::vec3(x, y, z), vertices, triIndices, uvs);
                    }
                    // The space behind of this voxel is empty
                    if (cache.getVoxelType(xOrigin, 0, zOrigin, x, y, z + 1) == VOXEL_TYPE_EMPTY)
                    {
                        backFace(voxelType, glm::vec3(x, y, z), vertices, triIndices, uvs);
                    }
                    // The space in front of this voxel is empty
                    if (cache.getVoxelType(xOrigin, 0, zOrigin, x, y, z - 1) == VOXEL_TYPE_EMPTY)
                    {
                        frontFace(voxelType, glm::vec3(x, y, z), vertices, triIndices, uvs);
                    }
                }
            }
        }
    }

    struct chunk {

    };

    class chunkLoader{
        Scene* scene;
        int chunkDepth;
        GLuint shader;

    public:
        chunkLoader(Scene* scene, int chunkDepth, GLuint shader){
            this->scene = scene;
            this->chunkDepth = chunkDepth;
            this->shader = shader;
        }

        void update(glm::vec3 worldPosition)
        {

        }
    };

}


#endif //CG_PROJECT_VOXEL_H
