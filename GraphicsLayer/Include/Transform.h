//
// Created by Torben Bernhard on 3/30/24.
//

#ifndef CG_PROJECT_TRANSFORM_H
#define CG_PROJECT_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>

class Transform
{
public:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    Transform()
    {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        rotation = glm::quat();
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    glm::mat4 getMatrix();
    glm::vec3 getForward();
    glm::vec3 getRight();
    glm::vec3 getUp();
};

#endif //CG_PROJECT_TRANSFORM_H
