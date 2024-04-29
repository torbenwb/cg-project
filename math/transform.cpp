//
// Created by Torben Bernhard on 4/6/24.
//

#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace math
{
    glm::mat4 Transform::getMatrix()
    {
        glm::mat4 transformation = glm::mat4(1.0f);

        transformation = glm::translate(transformation, position);
        transformation = glm::toMat4(rotation) * transformation;
        transformation = glm::scale(transformation,scale);

        return transformation;
    }

    glm::vec3 Transform::getForward() {
        glm::mat4 transform = getMatrix();
        return glm::vec3(transform[0][2], transform[1][2], transform[2][2]);
    }

    glm::vec3 Transform::getRight() {
        glm::mat4 transform = getMatrix();
        return -glm::vec3(transform[0][0], transform[1][0], transform[2][0]);
    }

    glm::vec3 Transform::getUp() {
        glm::mat4 transform = getMatrix();
        return -glm::vec3(transform[0][1], transform[1][1], transform[2][1]);
    }
}