//
// Created by Torben Bernhard on 4/11/24.
//

#ifndef CG_PROJECT_SCENE_H
#define CG_PROJECT_SCENE_H

#include "glad.h"
#include "glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <unordered_map>
#include "mesh.h"
#include "../math/transform.h"
#include <string>

namespace open_gl
{
    struct entity {
        const unsigned char ACTIVE = 1;
        const unsigned char INACTIVE = 2;
        const unsigned char DEAD = 0;
    private:
        unsigned char status = 1;
    public:
        std::string name;

        bool getActive() {return status == ACTIVE;}
        bool getDead() {return status == DEAD;}
        void setActive(bool active){status = active ? ACTIVE : INACTIVE; }
        void destroy() { status = DEAD; }

        entity(){}
        entity(std::string name){this->name = name;}
    };

    struct transform {
        transform(){}
        transform(math::Transform* t){
            position = t->position;
            rotation = t->rotation;
            scale = t->scale;
        }
        transform(glm::vec3 position){
            this->position = position;
        }

        glm::vec3 position = glm::vec3(0,0,0);
        glm::quat rotation = glm::quat();
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

        glm::mat4 matrix(){
            glm::mat4 transformation = glm::mat4(1.0f);

            transformation = glm::translate(transformation, position);
            transformation = glm::toMat4(rotation) * transformation;
            transformation = glm::scale(transformation,scale);

            return transformation;
        }
    };

    struct mesh {
        mesh(){}
        mesh(Mesh* meshptr, GLuint shader){
            shaderProgram = shader;
            vao = meshptr->getVAO();
            vbo = meshptr->getVBO();
            ebo = meshptr->getEBO();
            vCount = meshptr->getVertexCount();
            tCount = meshptr->getTriIndexCount();
        }
        GLuint shaderProgram;
        GLuint vao;
        GLuint vbo;
        GLuint ebo;

        unsigned int vCount;
        unsigned int tCount;

        void setAttributes()
        {
            const char* VERT_ATTRIB_NAME = "point";
            const char* NORMAL_ATTRIB_NAME = "normal";
            const char* UV_ATTRIB_NAME = "uv";

            glUseProgram(shaderProgram);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            int normalOffset = (vCount * sizeof(glm::vec3));
            int uvOffset = normalOffset + vCount * sizeof(glm::vec3);

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

        void renderInstance(glm::mat4 model){
            setAttributes();

            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glDrawElements(GL_TRIANGLES, tCount, GL_UNSIGNED_INT, 0);


        }
    };


    class Scene {
    private:
        unsigned int next_id = 0;

        glm::mat4 view;
        glm::mat4 projection;

        std::vector<entity> entities;
        std::vector<GLuint> shaders;
        std::vector<mesh> meshes;
        std::vector<transform> transforms;

        std::unordered_map<unsigned int, unsigned int> transformTable;
        std::unordered_map<unsigned int, unsigned int> meshTable;

        // Set scene uniforms for a single shader program
        void setSceneUniforms(GLuint shaderProgram);

    public:
        Scene();

        void setView(glm::mat4 view);
        void setProjection(glm::mat4 projection);
        void render();

        // Create a new entity with name and return id (index)
        unsigned int newEntity(std::string name, transform t);
        void setEntityActive(unsigned int entityId, bool newActive);
        void destroyEntity(unsigned int entityId);
        void addMesh(unsigned int entityId, mesh m);
        transform getTransform(unsigned int entityId);
        mesh getMesh(unsigned int entityId);
    };
}



#endif //CG_PROJECT_SCENE_H
