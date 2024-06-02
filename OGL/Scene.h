//
// Created by Torben Bernhard on 5/10/24.
//

#ifndef CG_PROJECT_SCENE_H
#define CG_PROJECT_SCENE_H

#include <vector>
#include "MeshRenderer.h"
#include "Transform.h"

namespace OGL
{
    class Scene
    {
    private:
        std::vector<MeshRenderer> meshRenderers;
        std::vector<GLuint> shaders;
        std::vector<unsigned int> meshRendererPool;


    public:
        Scene();
        void render(glm::mat4 view, glm::mat4 projection);

        unsigned int addMeshRenderer(MeshData meshData, GLuint shaderProgram, Transform transform);
        bool updateMeshRendererTransform(unsigned int index, Transform transform);
        bool removeMeshRenderer(unsigned int index);
        bool updateMeshRendererMeshData(unsigned int index, MeshData);
        bool setMeshRendererActive(unsigned int index, bool active);
    };
}



#endif //CG_PROJECT_SCENE_H
