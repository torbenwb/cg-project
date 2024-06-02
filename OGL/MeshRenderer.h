//
// Created by Torben Bernhard on 5/10/24.
//

#ifndef CG_PROJECT_MESHRENDERER_H
#define CG_PROJECT_MESHRENDERER_H

#include "MeshData.h"
#include "Transform.h"

namespace OGL
{
    struct MeshRenderer
    {
    private:


        GLuint shaderProgram;

    public:
        MeshData meshData;
        bool active;
        Transform transform;

        MeshRenderer(MeshData _meshData, GLuint _shaderProgram, Transform _transform):
        active(true), meshData(_meshData), shaderProgram(_shaderProgram), transform(_transform) {}

        void render()
        {
            meshData.renderInstance(transform.getMatrix(), shaderProgram);
        }
    };
}

#endif //CG_PROJECT_MESHRENDERER_H
