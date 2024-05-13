//
// Created by Torben Bernhard on 4/6/24.
//

#ifndef CG_PROJECT_MESH_H
#define CG_PROJECT_MESH_H

#include "glad.h"
#include "glfw3.h"
#include <vector>
#include <glm/glm.hpp>

namespace open_gl
{
    class Mesh {
        private:
            // Mesh Data
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> normals;
            std::vector<glm::vec2> uvs;
            std::vector<int> triIndices;
            // GPU buffer ids
            GLuint vao;
            GLuint vbo;
            GLuint ebo;

            void setAttributes(GLuint shaderProgram);

            void clearMeshData();
            void clearBuffers();

            void addVertex(float x, float y, float z);
            void addNormal(float x, float y, float z);
            void addUV(float u, float v);
            void addTriangle(int a, int b, int c);
    public:
        GLuint getVAO(){return vao;}
        GLuint getVBO(){return vbo;}
        GLuint getEBO(){return ebo;}
        GLuint getVertexCount(){return vertices.size();}
        GLuint getTriIndexCount(){return triIndices.size();}

        Mesh();
        ~Mesh();
        void buffer();
        void plane();
        void cube();
        // Makes no assumption about uniforms but does require
        // the shader program
        void render(GLuint shaderProgram, glm::mat4 model);
        void renderInstances(GLuint shaderProgram, glm::mat4 *models, int n);
        std::vector<glm::vec3> getVertices() { return vertices; }
        std::vector<int> getTriangles() { return triIndices; }

        void setVertices(std::vector<glm::vec3> vertices);
        void setNormals(std::vector<glm::vec3> normals);
        void setUVs(std::vector<glm::vec2> uvs);
        void setTriIndices(std::vector<int> indices);

        void recalculateNormals();
    };
}



#endif //CG_PROJECT_MESH_H
