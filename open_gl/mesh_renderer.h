//
// Created by Torben Bernhard on 4/6/24.
//

#ifndef CG_PROJECT_MESH_RENDERER_H
#define CG_PROJECT_MESH_RENDERER_H

#include "mesh.h"
#include "renderer.h"

namespace open_gl
{
    class mesh_renderer{
    public:
        Mesh* mesh;
        GLuint shader;

    };
}



#endif //CG_PROJECT_MESH_RENDERER_H
