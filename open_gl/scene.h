//
// Created by Torben Bernhard on 4/11/24.
//

#ifndef CG_PROJECT_SCENE_H
#define CG_PROJECT_SCENE_H

#include "glad.h"
#include "glfw3.h"
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include "mesh.h"
#include "../math/transform.h"
#include <string>

namespace open_gl
{
    struct transform {
        glm::vec3 position = glm::vec3(0,0,0);
        glm::quat rotation = glm::quat();
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    };

    struct MeshRenderer
    {
        Mesh* mesh;
        math::Transform* transform;
        bool active = true;

        MeshRenderer(Mesh* mesh, math::Transform* transform)
        {
            this->mesh = mesh;
            this->transform = transform;
        }
    };

    struct Light
    {
        math::Transform* transform;
        float intensity;

        Light(math::Transform* transform, float intensity)
        {
            this->transform = transform;
            this->intensity = intensity;
        }
    };

    class Scene {
    private:
        unsigned int next_id = 0;

        glm::mat4 view;
        glm::mat4 projection;
        glm::vec3 light;
        std::vector<GLuint> shaderPrograms;
        std::vector<Light> lights;
        std::unordered_map<GLuint, std::vector<MeshRenderer>> meshRendererMap;

        std::vector<unsigned int> entity_ids;
        std::vector<std::string> entity_names;
        std::vector<transform> entity_transforms;
        std::vector<Mesh*> entity_meshes;
        std::vector<GLuint> entity_shaders;

        // Set scene uniforms for a single shader program
        void setSceneUniforms(GLuint shaderProgram);

    public:
        Scene();

        void setView(glm::mat4 view);
        void setProjection(glm::mat4 projection);
        void render();
        void addMeshRenderer(Mesh* mesh, math::Transform* transform, GLuint shader);
        void toggleMeshRendererActive(GLuint shaderProgram, int index, bool active);

        unsigned int newEntity(std::string name);


        void addLight(math::Transform* transform, float intensity);
        void setLight(glm::vec3 light) { this->light = light; }
    };
}



#endif //CG_PROJECT_SCENE_H
