//
// Created by Torben Bernhard on 4/6/24.
//

#include "mesh.h"
#include <iostream>
#include <stdio.h>
#include <glm/gtc/type_ptr.hpp>

namespace open_gl
{
    void Mesh::buffer() {
        //clearBuffers();

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

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
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triBufferSize, triIndices.data(), GL_STATIC_DRAW);

    }

    void Mesh::clearMeshData() {
        vertices.clear();
        normals.clear();
        uvs.clear();
        triIndices.clear();
    }

    void Mesh::clearBuffers() {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &vao);
        glDeleteBuffers(1, &ebo);
    }

    Mesh::Mesh() {

    }

    Mesh::~Mesh() {
        clearBuffers();
    }

    void Mesh::cube() {
        clearMeshData();
        vertices = {
                // Front face
                {-1.0f, 1.0f, -1.0f},
                {1.0f, 1.0f, -1.0f},
                {-1.0f, -1.0f, -1.0f},
                {1.0f, -1.0f, -1.0f},
                // Back face
                {-1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f},
                {-1.0f, -1.0f, 1.0f},
                {1.0f, -1.0f, 1.0f},
                // Top Face
                {-1.0f, 1.0f, -1.0f},
                {1.0f, 1.0f, -1.0f},
                {-1.0f, 1.0f, 1.0f},
                {1.0f, 1.0f, 1.0f},
                // Bottom Face
                {-1.0f, -1.0f, -1.0f},
                {1.0f, -1.0f, -1.0f},
                {-1.0f, -1.0f, 1.0f},
                {1.0f, -1.0f, 1.0f},
                // Left face
                {-1.0f, 1.0f, -1.0f},
                {-1.0f, 1.0f, 1.0f},
                {-1.0f, -1.0f, -1.0f},
                {-1.0f, -1.0f, 1.0f},
                // Right face
                {1.0f, 1.0f, -1.0f},
                {1.0f, 1.0f, 1.0f},
                {1.0f, -1.0f, -1.0f},
                {1.0f, -1.0f, 1.0f}
        };

        triIndices = {
            // Front face
            0, 1, 2,
            1, 3, 2,
            // Back Face
            6, 5, 4,
            6, 7, 5,
            // Top face
            10, 9, 8,
            10, 11, 9,
            // Bottom face
            13, 14, 12,
            15, 14, 13,
            // Left face
            18, 17, 16,
            18, 19, 17,
            // Right face
            21, 22, 20,
            23, 22, 21
        };
        buffer();
    }

    void Mesh::addVertex(float x, float y, float z) {
        vertices.emplace_back(glm::vec3(x, y, z));
    }

    void Mesh::addNormal(float x, float y, float z) {
        normals.emplace_back(glm::vec3(x, y, z));
    }

    void Mesh::addUV(float u, float v) {
        uvs.emplace_back(glm::vec2(u, v));
    }

    void Mesh::addTriangle(int a, int b, int c) {
        triIndices.emplace_back(a);
        triIndices.emplace_back(b);
        triIndices.emplace_back(c);
    }

    void Mesh::render(GLuint shaderProgram, glm::mat4 model) {
        setAttributes(shaderProgram);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, triIndices.size(), GL_UNSIGNED_INT, 0);
    }

    void Mesh::plane() {
        //clearMeshData();
        addVertex(-1.0f, -1.0f, 0.0f);
        addVertex(-1.0f, 1.0f, 0.0f);
        addVertex(1.0f, 1.0f, 0.0f);
        addVertex(1.0f, -1.0f, 0.0f);

        addNormal(0.0f, 0.0f, -1.0f);
        addNormal(0.0f, 0.0f, -1.0f);
        addNormal(0.0f, 0.0f, -1.0f);
        addNormal(0.0f, 0.0f, -1.0f);

        addTriangle(0, 1, 2);
        addTriangle(0,2, 3);
        buffer();
    }

    void Mesh::recalculateNormals() {
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

        buffer();
    }

    void Mesh::setAttributes(GLuint shaderProgram) {
        const char* VERT_ATTRIB_NAME = "point";
        const char* NORMAL_ATTRIB_NAME = "normal";
        const char* UV_ATTRIB_NAME = "uv";

        glUseProgram(shaderProgram);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        int normalOffset = (vertices.size() * sizeof(glm::vec3));
        int uvOffset = normalOffset + normals.size() * sizeof(glm::vec3);

        GLint vertexAttributeId = glGetAttribLocation(shaderProgram, VERT_ATTRIB_NAME);
        glEnableVertexAttribArray(vertexAttributeId);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        GLint normalAttributeId = glGetAttribLocation(shaderProgram, NORMAL_ATTRIB_NAME);
        glEnableVertexAttribArray(normalAttributeId);
        glVertexAttribPointer(normalAttributeId, 3, GL_FLOAT, GL_FALSE, 0, (void*)normalOffset);

        GLint uvAttributeId = glGetAttribLocation(shaderProgram, UV_ATTRIB_NAME);
        glEnableVertexAttribArray(uvAttributeId);
        glVertexAttribPointer(uvAttributeId, 2, GL_FLOAT, GL_FALSE, 0, (void*)uvOffset);
    }

    void Mesh::renderInstances(GLuint shaderProgram, glm::mat4* models, int n) {
        setAttributes(shaderProgram);

        for(int i = 0; i < n; i++)
        {
            glm::mat4 model = models[i];
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glDrawElements(GL_TRIANGLES, triIndices.size(), GL_UNSIGNED_INT, 0);
        }
    }

    void Mesh::setVertices(std::vector<glm::vec3> vertices) {
        this->vertices.clear();
        for(int i = 0; i < vertices.size(); i++) {
            this->vertices.emplace_back(vertices[i]);
        }
    }

    void Mesh::setNormals(std::vector<glm::vec3> normals) {
        this->normals.clear();
        for(int i = 0; i < normals.size(); i++){
            this->normals.emplace_back(normals[i]);
        }
    }

    void Mesh::setUVs(std::vector<glm::vec2> uvs) {
        this->uvs.clear();
        for(int i = 0; i < uvs.size(); i++){
            this->uvs.emplace_back(uvs[i]);
        }
    }

    void Mesh::setTriIndices(std::vector<int> indices) {
        this->triIndices.clear();
        for(int i = 0; i < indices.size(); i++){
            this->triIndices.emplace_back(indices[i]);
        }
    }


}

