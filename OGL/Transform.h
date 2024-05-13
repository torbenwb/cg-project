//
// Created by Torben Bernhard on 5/10/24.
//

#ifndef CG_PROJECT_TRANSFORM_H
#define CG_PROJECT_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace OGL
{
    struct Transform
    {
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::quat rotation = glm::quat();
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

        Transform(){}
        Transform(glm::vec3 _position): position(_position), rotation(glm::quat()), scale(glm::vec3(1, 1, 1)){}
        Transform(glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale)
                : position(_position), rotation(_rotation), scale(_scale){}

        glm::mat4 getMatrix()
        {
            glm::mat4 transformation = glm::mat4(1.0f);

            transformation = glm::translate(transformation, position);
            transformation = glm::toMat4(rotation) * transformation;
            transformation = glm::scale(transformation,scale);

            return transformation;
        }

        glm::vec3 getForward() {
            glm::mat4 transform = getMatrix();
            return glm::vec3(transform[0][2], transform[1][2], transform[2][2]);
        }

        glm::vec3 getRight() {
            glm::mat4 transform = getMatrix();
            return -glm::vec3(transform[0][0], transform[1][0], transform[2][0]);
        }

        glm::vec3 getUp() {
            glm::mat4 transform = getMatrix();
            return -glm::vec3(transform[0][1], transform[1][1], transform[2][1]);
        }
    };
}


#endif //CG_PROJECT_TRANSFORM_H
