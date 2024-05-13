//
// Created by Torben Bernhard on 5/11/24.
//

#ifndef CG_PROJECT_CHUNK_H
#define CG_PROJECT_CHUNK_H

#include <vector>
#include <glm/glm.hpp>
#include "../OGL/Mesh.h"

namespace Voxel
{
    class Chunk
    {
    private:
        constexpr static const float FACE_SIZE = 0.5f;
        static const char TOP_FACE = 0;
        static const char BOTTOM_FACE = 1;
        static const char LEFT_FACE = 2;
        static const char RIGHT_FACE = 3;
        static const char BACK_FACE = 4;
        static const char FRONT_FACE = 5;


        static void topFace(const unsigned short voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs);
        static void bottomFace(const unsigned short voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs);
        static void leftFace(const unsigned short voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs);
        static void rightFace(const unsigned short voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs);
        static void backFace(const unsigned short voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs);
        static void frontFace(const unsigned short voxelType, glm::vec3 offset, std::vector<glm::vec3>& vertices, std::vector<int>& indices, std::vector<glm::vec2>& uvs);
        static void getFaceUVs(const char face, const unsigned int voxelType, std::vector<glm::vec2>& uvs);
        static void getAtlasUVs(int x, int y, int width, int height, std::vector<glm::vec2> &uvs);




    public:
        static const unsigned int WIDTH;
        static const unsigned int HEIGHT;

        glm::vec3 origin;
        OGL::Mesh* mesh;
        static Chunk generateChunk(glm::vec3 origin);

        Chunk(glm::vec3 _origin, OGL::Mesh* _mesh) : origin(_origin), mesh(_mesh){}
        Chunk(const Chunk& other) : origin(other.origin), mesh(other.mesh){}

    };
}



#endif //CG_PROJECT_CHUNK_H
