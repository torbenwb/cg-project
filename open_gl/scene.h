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

namespace open_gl
{
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
        glm::mat4 view;
        glm::mat4 projection;
        glm::vec3 light;
        std::vector<GLuint> shaderPrograms;
        std::vector<Light> lights;
        std::unordered_map<GLuint, std::vector<MeshRenderer>> meshRendererMap;

        // Set scene uniforms for a single shader program
        void setSceneUniforms(GLuint shaderProgram);

    public:
        void setView(glm::mat4 view);
        void setProjection(glm::mat4 projection);
        void render();
        void addMeshRenderer(Mesh* mesh, math::Transform* transform, GLuint shader);
        void toggleMeshRendererActive(GLuint shaderProgram, int index, bool active);



        void addLight(math::Transform* transform, float intensity);
        void setLight(glm::vec3 light) { this->light = light; }
    };
}



#endif //CG_PROJECT_SCENE_H
