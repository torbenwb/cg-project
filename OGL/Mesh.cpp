//
// Created by Torben Bernhard on 5/10/24.
//

#include "Mesh.h"

namespace OGL
{
    void Mesh::bufferToGPU(bool recalculateNormals)
    {
        deleteBuffers();
        if (recalculateNormals) this->calculateNormals();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        int numVertices = vertices.size();
        int vertexBufferSize = numVertices * sizeof(glm::vec3);

        int numNormals = normals.size();
        int normalBufferSize = numNormals * sizeof(glm::vec3);

        int numUVs = uvs.size();
        int uvBufferSize = numUVs * sizeof (glm::vec2);

        int fullBufferSize = vertexBufferSize + normalBufferSize + uvBufferSize;

        glBufferData(GL_ARRAY_BUFFER, fullBufferSize, NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexBufferSize, vertices.data());
        glBufferSubData(GL_ARRAY_BUFFER, vertexBufferSize, normalBufferSize, normals.data());
        glBufferSubData(GL_ARRAY_BUFFER, vertexBufferSize + normalBufferSize, uvBufferSize, uvs.data());

        int numTriIndices = triIndices.size();
        int triBufferSize = numTriIndices * sizeof(int);
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triBufferSize, triIndices.data(), GL_STATIC_DRAW);

    }

    void Mesh::calculateNormals() {
        normals.clear();

        for(int i = 0; i < vertices.size(); i++)
        {
            normals.emplace_back(glm::vec3(0, 0, 0));
        }

        for(int i = 0; i < triIndices.size(); i += 3)
        {
            int a = triIndices[i];
            int b = triIndices[i + 1];
            int c = triIndices[i + 2];

            glm::vec3 ab = vertices[b] - vertices[a];
            glm::vec3 ac = vertices[c] - vertices[a];
            glm::vec3 n = glm::cross(ab, ac);

            n = glm::normalize(n);

            normals[a] += n;
            normals[b] += n;
            normals[c] += n;
        }

        for(auto & normal : normals)
        {
            normal = glm::normalize(normal);
        }
    }
}
