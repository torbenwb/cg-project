//
// Created by Torben Bernhard on 4/27/24.
//

#ifndef CG_PROJECT_ATLAS_H
#define CG_PROJECT_ATLAS_H

#include <vector>
#include <glm/glm.hpp>

namespace texture_images
{
    class atlas
    {
    public:
        static void getUVs(int x, int y, int width, int height, std::vector<glm::vec2>& uvs, int rotation = 0);
    };

    void atlas::getUVs(int x, int y, int width, int height, std::vector<glm::vec2> &uvs, int rotation) {
        float edgeOffset = 0.01f;
        float l = ((float)x / width) + edgeOffset;
        float r = ((float)(x + 1) / width) - edgeOffset;
        float b = ((float)y / height) + edgeOffset;
        float t = ((float)(y + 1) / height) - edgeOffset;

        uvs.emplace_back(glm::vec2(l, b));
        uvs.emplace_back(glm::vec2(r, b));
        uvs.emplace_back(glm::vec2(l, t));
        uvs.emplace_back(glm::vec2(r, t));

    }
}


#endif //CG_PROJECT_ATLAS_H
