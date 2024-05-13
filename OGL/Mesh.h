//
// Created by Torben Bernhard on 5/10/24.
//

#ifndef CG_PROJECT_MESH_H
#define CG_PROJECT_MESH_H

#include "glad.h"
#include "glfw3.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "MeshData.h"

namespace OGL
{
    class Mesh
    {
    private:
        GLuint VBO, VAO, EBO;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;
        std::vector<int> triIndices;

        void bufferToGPU(bool recalculateNormals = true);
        void calculateNormals();
        void deleteBuffers(){
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &VAO);
            glDeleteBuffers(1, &EBO);
        }

    public:
        Mesh(){}
        Mesh(std::vector<glm::vec3> _vertices,
            std::vector<glm::vec3> _normals,
            std::vector<glm::vec2> _uvs,
            std::vector<int> _triIndices
        ): vertices(_vertices), normals(_normals), uvs(_uvs), triIndices(_triIndices)
        {
            bufferToGPU(false);
        }
        Mesh(std::vector<glm::vec3> _vertices,
             std::vector<glm::vec2> _uvs,
             std::vector<int> _triIndices
        ): vertices(_vertices), uvs(_uvs), triIndices(_triIndices)
        {
            bufferToGPU();
        }

        void setVertices(std::vector<glm::vec3> vertices){
            this->vertices = vertices;
            bufferToGPU();
        }

        void setUVs(std::vector<glm::vec2> uvs){
            this->uvs = uvs;
            bufferToGPU();
        }

        MeshData getMeshData() {
            return MeshData(VAO, VBO, EBO, vertices.size(), triIndices.size());
        }

        ~Mesh() {deleteBuffers();}
    };
}




#endif //CG_PROJECT_MESH_H
