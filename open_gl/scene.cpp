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
    }

    void Scene::render() {
        glClearColor(0.3, 0.8, 0.99, 0.5);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for(int i = 0; i < shaders.size(); i++){
            setSceneUniforms(shaders[i]);
        }

        for (unsigned int i = 0; i < entities.size(); i++){
            if (!entities[i].getActive()) continue;
            unsigned int e_id = i;
            transform t = getTransform(e_id);
            mesh m = getMesh(e_id);
            m.renderInstance(t.matrix());
        }


        glFlush();
    }

    void Scene::setView(glm::mat4 view) { this->view = view; }

    void Scene::setProjection(glm::mat4 projection) { this->projection = projection; }


    Scene::Scene() {

    }

    unsigned int Scene::newEntity(std::string name, transform t)
    {
        entities.emplace_back(entity(name));
        transformTable[entities.size() - 1] = transforms.size();
        transforms.emplace_back(t);
        return entities.size() - 1;
    }

    void Scene::setEntityActive(unsigned int eId, bool newActive){
        entities[eId].setActive(newActive);
    }

    void Scene::destroyEntity(unsigned int eId){
        entities[eId].destroy();
    }

    // Add a mesh component to the scene
    void Scene::addMesh(unsigned int entityId, mesh m) {
        meshTable[entityId] = meshes.size();
        meshes.emplace_back(m);
        shaders.emplace_back(m.shaderProgram);
    }

    transform Scene::getTransform(unsigned int e_id){
        return transforms[transformTable[e_id]];
    }

    mesh Scene::getMesh(unsigned int e_id){

        return meshes[meshTable[e_id]];
    }
}