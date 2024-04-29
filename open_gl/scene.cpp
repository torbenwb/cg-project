//
// Created by Torben Bernhard on 4/11/24.
//

#include "scene.h"
#include <glm/gtc/type_ptr.hpp>

namespace open_gl
{

    void Scene::setSceneUniforms(GLuint shaderProgram) {
        // Set view - camera location / rotation
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        // Set perspective
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "perspective"), 1, GL_FALSE, glm::value_ptr(projection));

        //printf("light position: (%f, %f, %f)\n",light.x, light.y, light.z);
        glUniform3fv(glGetUniformLocation(shaderProgram, "lightPosition"), 1, glm::value_ptr(light));
    }

    void Scene::render() {
        glClearColor(0.3, 0.8, 0.99, 0.5);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(int i = 0; i < shaderPrograms.size(); i++)
        {
            setSceneUniforms(shaderPrograms[i]);

            for(int j = 0; j < meshRendererMap[shaderPrograms[i]].size(); j++)
            {
                if (!meshRendererMap[shaderPrograms[i]][j].active) continue;
                GLuint shaderProgram = shaderPrograms[i];
                math::Transform meshTransform = *meshRendererMap[shaderPrograms[i]][j].transform;

                meshRendererMap[shaderPrograms[i]][j].mesh->render(shaderPrograms[i], meshTransform.getMatrix());
            }
        }

        glFlush();
    }

    void Scene::setView(glm::mat4 view) { this->view = view; }

    void Scene::setProjection(glm::mat4 projection) { this->projection = projection; }

    void Scene::addMeshRenderer(Mesh *mesh, math::Transform * transform, GLuint shader)
    {
        if (std::find(shaderPrograms.begin(), shaderPrograms.end(), shader) == shaderPrograms.end())
        {
            shaderPrograms.emplace_back(shader);
        }

        if (meshRendererMap.find(shader) != meshRendererMap.end()) {
            meshRendererMap[shader].emplace_back(MeshRenderer(mesh, transform));
        }
        else {
            meshRendererMap[shader] = std::vector<MeshRenderer>();
            meshRendererMap[shader].emplace_back(MeshRenderer(mesh, transform));
        }
    }

    void Scene::addLight(math::Transform* transform, float intensity) {
        lights.emplace_back(Light(transform, intensity));
    }

    void Scene::toggleMeshRendererActive(GLuint shaderProgram, int index, bool active) {
        if (meshRendererMap.find(shaderProgram) == meshRendererMap.end()) return;

        meshRendererMap[shaderProgram][index].active = active;
    }

}