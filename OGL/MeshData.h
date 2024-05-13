//
// Created by Torben Bernhard on 5/10/24.
//

#ifndef CG_PROJECT_MESHDATA_H
#define CG_PROJECT_MESHDATA_H

#include "glad.h"
#include "glfw3.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace OGL
{
    // Contains OpenGL rendering data for a mesh which
    // has already been buffered to the GPU
    struct MeshData
    {
    private:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;
        unsigned int V_COUNT;
        unsigned int T_COUNT;
    public:
        void debugLog(){
            printf("Mesh Data Debug Log: VAO: %d, VBO: %d, EBO: %d, V_COUNT: %d, T_COUNT: %d\n",
                   VAO, VBO, EBO, V_COUNT, T_COUNT);
        }

        MeshData(GLuint _VAO, GLuint _VBO, GLuint _EBO, unsigned int _V_COUNT, unsigned int _T_COUNT)
        : VAO(_VAO), VBO(_VBO), EBO(_EBO), V_COUNT(_V_COUNT), T_COUNT(_T_COUNT) {}

        void setAttributes(const GLuint shaderProgram)
        {
            const char* VERT_ATTRIB_NAME = "point";
            const char* NORMAL_ATTRIB_NAME = "normal";
            const char* UV_ATTRIB_NAME = "uv";

            glUseProgram(shaderProgram);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            int normalOffset = (V_COUNT * sizeof(glm::vec3));
            int uvOffset = normalOffset + V_COUNT * sizeof(glm::vec3);

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

        void renderInstance(const glm::mat4 model, const GLuint shaderProgram)
        {
            setAttributes(shaderProgram);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glDrawElements(GL_TRIANGLES, T_COUNT, GL_UNSIGNED_INT, 0);

        }
    };
}

#endif //CG_PROJECT_MESHDATA_H
