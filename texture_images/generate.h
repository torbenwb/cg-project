//
// Created by Torben Bernhard on 4/27/24.
//

#ifndef CG_PROJECT_GENERATE_H
#define CG_PROJECT_GENERATE_H

#include <vector>
#include <glm/glm.hpp>

namespace texture_images
{
    class generate
    {
    public:
        static unsigned char* generateColorAtlasTexture(std::vector<glm::vec3> colors);
    };

    unsigned char *generate::generateColorAtlasTexture(std::vector<glm::vec3> colors) {
        unsigned char* data = new unsigned char[colors.size() * 3];
        for(int i = 0; i < colors.size(); i++)
        {
            data[i * 3] = colors[i].x;
            data[i * 3 + 1] = colors[i].y;
            data[i * 3 + 2] = colors[i].z;
        }
        return data;
    }
}

#endif //CG_PROJECT_GENERATE_H
