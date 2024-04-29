//
// Created by Torben Bernhard on 4/6/24.
//

#ifndef CG_PROJECT_CAMERA_H
#define CG_PROJECT_CAMERA_H

#include "../math/transform.h"
#include "../math/projection.h"
#include "mesh.h"
#include <vector>

namespace open_gl
{
    class camera {
    private:
    public:
        math::Transform transform;
        math::Projection projection;
        glm::vec4 clearColor;

        void render(GLuint shaderProgram);
    };
}



#endif //CG_PROJECT_CAMERA_H
