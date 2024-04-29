//
// Created by Torben Bernhard on 4/6/24.
//

#ifndef CG_PROJECT_PROJECTION_H
#define CG_PROJECT_PROJECTION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace math
{
    struct Projection
    {
        float fieldOfView;
        float aspectRatio;
        float nearClippingPlane;
        float farClippingPlane;

        Projection(){}

        Projection(float fieldOfView,
                   float aspectRatio,
                   float nearClippingPlane,
                   float farClippingPlane)
        {
            this->fieldOfView = fieldOfView;
            this->aspectRatio = aspectRatio;
            this->nearClippingPlane = nearClippingPlane;
            this->farClippingPlane = farClippingPlane;
        }

        glm::mat4 getMatrix()
        {
            return glm::perspective(fieldOfView, aspectRatio, nearClippingPlane, farClippingPlane);
        }
    };
}



#endif //CG_PROJECT_PROJECTION_H
