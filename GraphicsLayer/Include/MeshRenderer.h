//
// Created by Torben Bernhard on 3/28/24.
//

#ifndef CG_PROJECT_MESHRENDERER_H
#define CG_PROJECT_MESHRENDERER_H

#include <vector>
#include "MeshData.h"
#include "Transform.h"
#include "Projection.h"

class MeshRenderer
{
public:
    MeshData* meshData;

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    void Buffer();
    void Render(GLuint shaderProgram, Transform model, Transform view, Projection projection);

};

#endif //CG_PROJECT_MESHRENDERER_H
