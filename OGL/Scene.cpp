//
// Created by Torben Bernhard on 5/10/24.
//

#include "Scene.h"
#include "iostream"

namespace OGL
{

    void Scene::render(glm::mat4 view, glm::mat4 projection)
    {
        for(auto shader : shaders)
        {
            // Set view - camera location / rotation
            glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
            // Set perspective
            glUniformMatrix4fv(glGetUniformLocation(shader, "perspective"), 1, GL_FALSE, glm::value_ptr(projection));
        }

        glClearColor(0.3, 0.8, 0.99, 0.5);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(auto meshRenderer : meshRenderers){
            if (!meshRenderer.active) continue;

            meshRenderer.render();
        }

        glFlush();
    }

    unsigned int Scene::addMeshRenderer(MeshData meshData, GLuint shaderProgram, Transform transform) {
        if (std::find(shaders.begin(), shaders.end(), shaderProgram) == shaders.end())
        {
            shaders.emplace_back(shaderProgram);
        }

        // Use first available existing mesh renderer slot
        if (meshRendererPool.size() > 0)
        {
            unsigned int nextIndex = meshRendererPool.back();
            meshRendererPool.pop_back();
            meshRenderers[nextIndex] = MeshRenderer(meshData, shaderProgram, transform);
            return nextIndex;
        }
        else
        {
            unsigned int nextIndex = meshRenderers.size();
            meshRenderers.emplace_back(MeshRenderer(meshData, shaderProgram, transform));
            return nextIndex;
        }
    }

    bool Scene::updateMeshRendererTransform(unsigned int index, Transform transform) {
        if (index < 0 || index > meshRenderers.size()) return false;
        meshRenderers[index].transform = transform;
        return true;
    }

    bool Scene::removeMeshRenderer(unsigned int index) {
        if (index < 0 || index > meshRenderers.size()) return false;
        meshRendererPool.emplace_back(index);
        meshRenderers[index].active = false;

        return true;
    }

    Scene::Scene() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }


}