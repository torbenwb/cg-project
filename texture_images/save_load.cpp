//
// Created by Torben Bernhard on 5/11/24.
//

#include "save_load.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace texture_images
{
    unsigned char *save_load::loadImage(const char* filename, int& width, int& height, int& numChannels) {
        unsigned char* imageData = stbi_load(filename, &width, &height, &numChannels, 0);
        return imageData;
    }
}