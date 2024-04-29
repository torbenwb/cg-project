//
// Created by Torben Bernhard on 4/27/24.
//

#ifndef CG_PROJECT_SAVE_LOAD_H
#define CG_PROJECT_SAVE_LOAD_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace texture_images
{
    class save_load
    {
    public:
        static unsigned char* loadImage(const char* filename, int& width, int& height, int& numChannels);
    };

    unsigned char *save_load::loadImage(const char* filename, int& width, int& height, int& numChannels) {
        unsigned char* imageData = stbi_load(filename, &width, &height, &numChannels, 0);
        return imageData;
    }
}

#endif //CG_PROJECT_SAVE_LOAD_H
