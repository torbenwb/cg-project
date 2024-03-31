//
// Created by Torben Bernhard on 3/30/24.
//

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

glm::mat4 Transform::getMatrix()
{
    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, position);
    transformation = glm::toMat4(rotation) * transformation;
    transformation = glm::scale(transformation,scale);

    return transformation;
}