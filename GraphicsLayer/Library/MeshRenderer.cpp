//
// Created by Torben Bernhard on 3/28/24.
//

#include "glad.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void MeshRenderer::Buffer()
{
    if (meshData == NULL) return;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    int numVertices = meshData->vertices.size();
    int vertexSpaceSize = numVertices * sizeof(glm::vec3);

    int numNormals = meshData->normals.size();
    int normalSpaceSize = numNormals * sizeof(glm::vec3);

    int numColors = meshData->colors.size();
    int colorSpaceSize = numColors * sizeof(glm::vec3);

    int numUVs = meshData->uvs.size();
    int uvSpaceSize = numUVs * sizeof(glm::vec2);

    int fullBufferSize = vertexSpaceSize + normalSpaceSize + colorSpaceSize + uvSpaceSize;

    // Create and initialize a buffer object's data store (vertices, normals, colors)
    glBufferData(GL_ARRAY_BUFFER, fullBufferSize, NULL, GL_STATIC_DRAW);
    // Buffer vertices
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexSpaceSize, meshData->vertices.data());
    // Buffer Normals
    glBufferSubData(GL_ARRAY_BUFFER, vertexSpaceSize, normalSpaceSize, meshData->normals.data());
    // Buffer Colors
    glBufferSubData(GL_ARRAY_BUFFER, vertexSpaceSize + normalSpaceSize, colorSpaceSize, meshData->colors.data());
    // Buffer UVs
    glBufferSubData(GL_ARRAY_BUFFER, vertexSpaceSize + normalSpaceSize + colorSpaceSize, uvSpaceSize, meshData->uvs.data());


    int numIndices = meshData->triangles.size();
    int trisBufferSize = numIndices * sizeof(int);
    // Element Buffer
    glGenBuffers(1, &EBO);
    // Bind Buffer to EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Buffer triangle indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, trisBufferSize, meshData->triangles.data(), GL_STATIC_DRAW);
}

void MeshRenderer::Render(GLuint shaderProgram, Transform model, Transform view, Projection projection)
{
    int normalOffset = meshData->vertices.size() * sizeof(glm::vec3);
    int colorOffset = (meshData->vertices.size() + meshData->normals.size()) * sizeof(glm::vec3);
    int uvOffset = colorOffset + meshData->colors.size() * sizeof(glm::vec3);

    // TODO: Set Uniforms: modelView matrix, cameraView Matrix, cameraPerspective Matrix

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model.getMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view.getMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "perspective"), 1, GL_FALSE, glm::value_ptr(projection.getMatrix()));

    // TODO: Add support for 0 to many uniform variables

    glUseProgram(shaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    GLint vertexAttributeID = glGetAttribLocation(shaderProgram, "point");
    glEnableVertexAttribArray(vertexAttributeID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    GLint normalAttributeID = glGetAttribLocation(shaderProgram, "normal");
    glEnableVertexAttribArray(normalAttributeID);
    glVertexAttribPointer(normalAttributeID, 3, GL_FLOAT, GL_FALSE, 0, (void*)normalOffset);

    GLint colorAttributeID = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colorAttributeID);
    glVertexAttribPointer(colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, (void*)colorOffset);

    GLint uvAttributeID = glGetAttribLocation(shaderProgram, "uv");
    glEnableVertexAttribArray(uvAttributeID);
    glVertexAttribPointer(uvAttributeID, 2, GL_FLOAT, GL_FALSE, 0, (void*)uvOffset);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, meshData->triangles.size(), GL_UNSIGNED_INT, 0);
}