//
// Created by Torben Bernhard on 4/6/24.
//

#ifndef CG_PROJECT_RENDERER_H
#define CG_PROJECT_RENDERER_H

#include "../math/transform.h"

namespace open_gl
{
    class renderer {
    public:
        math::Transform transform;

        virtual void render() {}
    };
}



#endif //CG_PROJECT_RENDERER_H
