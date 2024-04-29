//
// Created by Torben Bernhard on 4/15/24.
//

#ifndef CG_PROJECT_VOXEL_H
#define CG_PROJECT_VOXEL_H

#include <vector>
#include <glm/glm.hpp>
#include "mesh.h"
#include "../noise/PerlinNoise.h"
#include "../texture_images/atlas.h"
#include <iostream>
#include <random>
#include <cmath>

namespace open_gl
{


    class voxel
    {
    public:
        static const char TOP_FACE = 0;
        static const char BOTTOM_FACE = 1;
        static const char LEFT_FACE = 2;
        static const char RIGHT_FACE = 3;
        static const char BACK_FACE = 4;
        static const char FRONT_FACE = 5;

        static const int width = 32;
        static const int height = 64;
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
        static uint getVoxelType(int x, int y, int z);
        static double randomDouble(double min, double max);
        static int randomInt(int min, int max);
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

        for(int x = 0; x < width; x++)
        {
            for(int z = 0; z < width; z++)
            {
                for(int y = 0; y < height; y++)
                {
                    int globalX = xOrigin + x;
                    int globalY = y;
                    int globalZ = zOrigin + z;
                    uint voxelType = getVoxelType(globalX, globalY, globalZ);

                    // If this voxel is empty then ignore and move to the next
                    if (voxelType == 0) continue;

                    // The space above this voxel is empty
                    if (getVoxelType(globalX, globalY + 1, globalZ) == 0)
                    {
                        topFace(voxelType, glm::vec3(x, y, z), vertices, indices, uvs);
                    }
                    // The space below this voxel is empty
                    if (getVoxelType(globalX, globalY - 1, globalZ) == 0)
                    {
                        bottomFace(voxelType, glm::vec3(x, y, z), vertices, indices, uvs);
                    }
                    // The space to the right of this voxel is empty
                    if (getVoxelType(globalX + 1, globalY, globalZ) == 0)
                    {
                        rightFace(voxelType, glm::vec3(x, y, z), vertices, indices, uvs);
                    }
                    // The space to the left of this voxel is empty
                    if (getVoxelType(globalX - 1, globalY, globalZ) == 0)
                    {
                        leftFace(voxelType, glm::vec3(x, y, z), vertices, indices, uvs);
                    }
                    // The space behind of this voxel is empty
                    if (getVoxelType(globalX, globalY, globalZ + 1) == 0)
                    {
                        backFace(voxelType, glm::vec3(x, y, z), vertices, indices, uvs);
                    }
                    // The space in front of this voxel is empty
                    if (getVoxelType(globalX, globalY, globalZ - 1) == 0)
                    {
                        frontFace(voxelType, glm::vec3(x, y, z), vertices, indices, uvs);
                    }
                }
            }
        }
        return toMesh(vertices, indices, uvs);
    }

    /*
     * Get voxel type at global x, y, z coordinates
     */
    uint voxel::getVoxelType(int x, int y, int z) {
        if (y <= 1) return 2;
        const int xSeed = 15;
        const int ySeed = 10;
        const int zSeed = 25;
        const int powSeed = 3;
        const double coefSeed = 1.5f;
        const double coefSeed2 = 3.0f;
        double h = noise::PerlinNoise::getInstance().noise((double)x / xSeed, (double)z / zSeed, (double)y / ySeed);

        h *= coefSeed;
        for(int i = 0; i < powSeed; i++) h *= h;
        h *= coefSeed2;

        if (y < h) return 1;

        return 0;
    }

    void voxel::getFaceUVs(const char face, const uint voxelType, std::vector<glm::vec2>& uvs) {
        if (voxelType == 2){
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
}


#endif //CG_PROJECT_VOXEL_H
