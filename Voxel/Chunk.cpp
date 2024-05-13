//
// Created by Torben Bernhard on 5/11/24.
//

#include "Chunk.h"
#include "World.h"
#include "iostream"

namespace Voxel
{
    const unsigned int Chunk::WIDTH = 32;
    const unsigned int Chunk::HEIGHT = 64;

    void Chunk::topFace(const unsigned short voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs) {
        int startIndex = vertices.size();
        vertices.emplace_back(offset + glm::vec3(-FACE_SIZE, FACE_SIZE, -FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(FACE_SIZE, FACE_SIZE, -FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(-FACE_SIZE, FACE_SIZE, FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(FACE_SIZE, FACE_SIZE, FACE_SIZE));

        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 0);
        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 3);
        indices.emplace_back(startIndex + 1);

        getFaceUVs(TOP_FACE, voxelType, uvs);
    }

    void Chunk::bottomFace(const unsigned short voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs) {
        int startIndex = vertices.size();
        vertices.emplace_back(offset + glm::vec3(-FACE_SIZE, -FACE_SIZE, -FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(FACE_SIZE, -FACE_SIZE, -FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(-FACE_SIZE, -FACE_SIZE, FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(FACE_SIZE, -FACE_SIZE, FACE_SIZE));

        indices.emplace_back(startIndex + 0);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 3);
        indices.emplace_back(startIndex + 2);

        getFaceUVs(BOTTOM_FACE, voxelType, uvs);
    }

    void Chunk::leftFace(const unsigned short voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs) {
        int startIndex = vertices.size();
        vertices.emplace_back(offset + glm::vec3(-FACE_SIZE, FACE_SIZE, -FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(-FACE_SIZE, FACE_SIZE, FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(-FACE_SIZE, -FACE_SIZE, -FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(-FACE_SIZE, -FACE_SIZE, FACE_SIZE));

        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 0);
        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 3);
        indices.emplace_back(startIndex + 1);

        getFaceUVs(LEFT_FACE, voxelType, uvs);
    }

    void Chunk::rightFace(const unsigned short voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs) {
        int startIndex = vertices.size();
        vertices.emplace_back(offset + glm::vec3(FACE_SIZE, FACE_SIZE, -FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(FACE_SIZE, FACE_SIZE, FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(FACE_SIZE, -FACE_SIZE, -FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(FACE_SIZE, -FACE_SIZE, FACE_SIZE));

        indices.emplace_back(startIndex + 0);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 3);
        indices.emplace_back(startIndex + 2);

        getFaceUVs(RIGHT_FACE, voxelType, uvs);
    }

    void Chunk::backFace(const unsigned short voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs) {
        int startIndex = vertices.size();
        vertices.emplace_back(offset + glm::vec3(-FACE_SIZE, FACE_SIZE, FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(FACE_SIZE, FACE_SIZE, FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(-FACE_SIZE, -FACE_SIZE, FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(FACE_SIZE, -FACE_SIZE, FACE_SIZE));

        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 0);
        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 3);
        indices.emplace_back(startIndex + 1);

        getFaceUVs(BACK_FACE, voxelType, uvs);
    }

    void Chunk::frontFace(const unsigned short voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs) {
        int startIndex = vertices.size();
        vertices.emplace_back(offset + glm::vec3(-FACE_SIZE, FACE_SIZE, -FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(FACE_SIZE, FACE_SIZE, -FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(-FACE_SIZE, -FACE_SIZE, -FACE_SIZE));
        vertices.emplace_back(offset + glm::vec3(FACE_SIZE, -FACE_SIZE, -FACE_SIZE));

        indices.emplace_back(startIndex + 0);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 2);
        indices.emplace_back(startIndex + 1);
        indices.emplace_back(startIndex + 3);
        indices.emplace_back(startIndex + 2);

        getFaceUVs(FRONT_FACE, voxelType, uvs);
    }

    void Chunk::getFaceUVs(const char face, const unsigned int voxelType, std::vector<glm::vec2> &uvs) {
        if (voxelType == World::VOXEL_TYPE_WATER){
            getAtlasUVs(0, 0, 2, 2, uvs);
            return;
        }
        if (voxelType == World::VOXEL_TYPE_SAND){
            getAtlasUVs(1, 0, 2, 2, uvs);
            return;
        }
        if (face == TOP_FACE) getAtlasUVs(0, 1, 2, 2, uvs);
        else if (face == LEFT_FACE) getAtlasUVs(1, 1, 2, 2, uvs);
        else if (face == RIGHT_FACE) getAtlasUVs(1, 1, 2, 2, uvs);
        else if (face == FRONT_FACE) getAtlasUVs(1, 1, 2, 2, uvs);
        else if (face == BACK_FACE) getAtlasUVs(1, 1, 2, 2, uvs);
        else getAtlasUVs(1, 1, 2, 2, uvs);
    }

    void Chunk::getAtlasUVs(int x, int y, int width, int height, std::vector<glm::vec2> &uvs){
        float edgeOffset = 0.01f;
        float l = ((float)x / width) + edgeOffset;
        float r = ((float)(x + 1) / width) - edgeOffset;
        float b = ((float)y / height) + edgeOffset;
        float t = ((float)(y + 1) / height) - edgeOffset;

        uvs.emplace_back(glm::vec2(l, b));
        uvs.emplace_back(glm::vec2(r, b));
        uvs.emplace_back(glm::vec2(l, t));
        uvs.emplace_back(glm::vec2(r, t));
    }

    Chunk Chunk::generateChunk(glm::vec3 origin) {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<int> triIndices;

        for(int _x = 0; _x < WIDTH; _x++){
            for(int _z = 0; _z < WIDTH; _z++){
                for(int _y = 0; _y < HEIGHT; _y++){

                    int x = (int)origin.x + _x;
                    int y = _y;
                    int z = (int)origin.z + _z;
                    glm::vec3 v = glm::vec3(_x, _y, _z);

                    if (World::getVoxelEmpty(x, y, z)) continue;
                    unsigned short voxelType = World::getVoxelType(x, y, z);

                    if (World::getVoxelEmpty(x, y + 1, z)) topFace(voxelType, v, vertices, triIndices, uvs);
                    if (World::getVoxelEmpty(x, y - 1, z)) bottomFace(voxelType, v, vertices, triIndices, uvs);
                    if (World::getVoxelEmpty(x + 1, y, z)) rightFace(voxelType, v, vertices, triIndices, uvs);
                    if (World::getVoxelEmpty(x - 1, y, z)) leftFace(voxelType, v, vertices, triIndices, uvs);
                    if (World::getVoxelEmpty(x, y, z + 1)) backFace(voxelType, v, vertices, triIndices, uvs);
                    if (World::getVoxelEmpty(x, y, z - 1)) frontFace(voxelType, v, vertices, triIndices, uvs);

                }
            }
        }

        OGL::Mesh* mesh = new OGL::Mesh(vertices, uvs, triIndices);
        //printf("generate chunk mesh ptr: %d\n", mesh);
        return {origin, mesh};
    }
}