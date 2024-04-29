//
// Created by Torben Bernhard on 4/11/24.
//

#ifndef CG_PROJECT_LIGHT_H
#define CG_PROJECT_LIGHT_H

#include "../math/transform.h"

namespace open_gl
{
    class Light
    {
    public:
        math::Transform transform;
        float intensity = 1.0f;
    };
}

#endif //CG_PROJECT_LIGHT_H
